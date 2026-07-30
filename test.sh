#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")"

CC="${1:-clang}"
echo "Using compiler: $CC"
overall_failed=0

test_mode() {
  local label="$1"
  shift

  echo ""
  echo "════════════════════════════════════════════════════════════════"
  echo "  Testing with $label ($*)"
  echo "════════════════════════════════════════════════════════════════"
  echo ""

  local mode_failed=0
  for src in examples/e*.c; do
    name="${src##*/}"
    name="${name%.c}"
    echo "=== $name ==="
    if ! "$CC" -Wall -Wextra -Werror "$@" -I. "$src" -o "/tmp/$name"; then
      echo "FAIL: compile $src"
      mode_failed=1
      continue
    fi
    if ! "/tmp/$name"; then
      echo "FAIL: run $name"
      mode_failed=1
    fi
  done

  if [ "$mode_failed" -ne 0 ]; then
    echo ""
    echo "SOME EXAMPLES FAILED ($label)"
    overall_failed=1
  else
    echo ""
    echo "ALL EXAMPLES PASSED ($label)"
  fi
}

# gnu11: C11 + GNU extensions (no -Wpedantic, so clang's
# -Wgnu-zero-variadic-macro-arguments is inactive)
test_mode "gnu11 (C11 + GNU extensions)" -std=gnu11

# c23: ISO C23 + -Wpedantic.
# Some compilers (GCC <15) use -std=c2x instead of -std=c23.
c23_std=-std=c23
if ! echo "int x;" | "$CC" -Werror "$c23_std" -c -x c - -o /dev/null &>/dev/null; then
  c23_std=-std=c2x
fi
# clang's -Wgnu-zero-variadic-macro-arguments fires on valid C23 zero-arg
# variadic macro invocations (C23 standardized this via __VA_OPT__; clang
# hasn't updated its diagnostic yet).  Suppress it for clang only.
c23_flags=("$c23_std" -Wpedantic)
case "$(basename "$CC")" in
  *clang*) c23_flags+=(-Wno-gnu-zero-variadic-macro-arguments) ;;
esac
test_mode "c23 (ISO C23, no GNU extensions)" "${c23_flags[@]}"

echo ""
if [ "$overall_failed" -ne 0 ]; then
  echo "════════════════════════════════════════════════════════════════"
  echo "  OVERALL: SOME TESTS FAILED"
  echo "════════════════════════════════════════════════════════════════"
  exit 1
fi

echo "════════════════════════════════════════════════════════════════"
echo "  OVERALL: ALL TESTS PASSED (gnu11 + c23)"
echo "════════════════════════════════════════════════════════════════"
