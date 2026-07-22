#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")"

overall_failed=0

test_mode() {
  local label="$1"
  local flag="$2"

  echo ""
  echo "════════════════════════════════════════════════════════════════"
  echo "  Testing with $label ($flag)"
  echo "════════════════════════════════════════════════════════════════"
  echo ""

  local mode_failed=0
  for src in examples/e*.c; do
    name="${src##*/}"
    name="${name%.c}"
    echo "=== $name ==="
    if ! clang -Wall -Wextra -Werror "$flag" -I. "$src" -o "/tmp/$name"; then
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

test_mode "gnu11 (C11 + GNU extensions)" "-std=gnu11"
test_mode "c23 (ISO C23, no GNU extensions)" "-std=c23"

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
