#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")"

# ── configuration ────────────────────────────────────────────────────────────

CC=${CC:-clang}
OPT_LEVELS=${OPT_LEVELS:--O0 -O1 -O2 -O3 -Os}
ASM_DIR="benchmark_asm"
REPORT="benchmark_report.txt"

# ── color handling ───────────────────────────────────────────────────────────

setup_colors() {
  if [ -t 1 ] && [ "${NO_COLOR:-}" = "" ]; then
    BOLD=$'\033[1m'
    PASS=$'\033[32m'
    WARN=$'\033[33m'
    FAIL=$'\033[31m'
    RST=$'\033[0m'
  else
    BOLD="" PASS="" WARN="" FAIL="" RST=""
  fi
}
setup_colors

# ── gather examples ─────────────────────────────────────────────────────────

examples=()
for src in examples/e*.c examples/demo.c; do
  [ -f "$src" ] && examples+=("$src")
done

if [ ${#examples[@]} -eq 0 ]; then
  echo "No example files found in examples/" >&2
  exit 1
fi

# ── helpers ──────────────────────────────────────────────────────────────────

# Safe grep -c: returns "0" even when nothing matches.
_count() {
  local out
  out=$(grep -cE "$1" "$2" 2>/dev/null) || true
  echo "${out:-0}"
}

# callq *%reg — vtable pointer loaded into a register (fully indirect)
count_fully_indirect() { _count '\bcallq?\s+\*%[a-z]' "$1"; }

# callq *symbol(%rip) or *symbol+offset(%rip) — vtable base known at link time
count_partial() { _count '\bcallq?\s+\*[A-Za-z_]' "$1"; }

# callq SymbolName — direct call to a named function (fully devirtualized)
find_trait_direct_calls() {
  grep -oE '\bcallq?\s+[A-Za-z_][A-Za-z0-9_]*' "$1" 2>/dev/null \
    | sed 's/^callq\?[[:space:]]*//' \
    | grep -iE '(Animal|Show|Pet|Reader|Logged|Container|Default|Dog_|IntBox_|StrBox_)' \
    | grep -vE '@PLT|puts|printf|__stack|__libc' \
    | sort -u || true
}

count_vtable_refs() { _count '_vtable' "$1"; }

count_trait_direct_calls() {
  local out
  out=$(find_trait_direct_calls "$1")
  if [ -n "$out" ]; then
    echo "$out" | wc -l
  else
    echo 0
  fi
}

get_main_range() {
  local asm="$1"
  local start
  start=$(grep -n '^[a-zA-Z_]*main:' "$asm" 2>/dev/null | head -1 | cut -d: -f1 || true)
  if [ -n "$start" ]; then
    sed -n "${start},$((start + 80))p" "$asm"
  else
    echo "(main not found in assembly)"
  fi
}

# ── compile ──────────────────────────────────────────────────────────────────

echo "${BOLD}Compiling examples to assembly...${RST}"
echo ""

rm -rf "$ASM_DIR"
mkdir -p "$ASM_DIR"

declare -A compile_ok

for opt in $OPT_LEVELS; do
  for src in "${examples[@]}"; do
    name="${src##*/}"
    name="${name%.c}"
    outfile="$ASM_DIR/${name}_${opt}.s"
    if $CC "$opt" -S -I. -o "$outfile" "$src" 2>"$ASM_DIR/${name}_${opt}.err"; then
      compile_ok["${name}_${opt}"]=1
    else
      compile_ok["${name}_${opt}"]=0
      echo "  ${FAIL}FAIL${RST}  $name $opt (compile error)"
    fi
  done
done

# ── summary table ───────────────────────────────────────────────────────────

echo ""
echo "${BOLD}Devirtualization summary (all examples combined)${RST}"
echo ""

printf "${BOLD}%-24s" "Category"
for opt in $OPT_LEVELS; do printf "| %-12s" "$opt"; done
printf "${RST}\n"

printf "%-24s" ""
for opt in $OPT_LEVELS; do printf "| %-12s" "------------"; done
printf "\n"

for label in "fully indirect" "partial devirt" "direct (devirt)" "vtable refs"; do
  printf "%-24s" "$label"
  for opt in $OPT_LEVELS; do
    total=0
    for src in "${examples[@]}"; do
      name="${src##*/}"
      name="${name%.c}"
      key="${name}_${opt}"
      [ "${compile_ok[$key]:-0}" != "1" ] && continue
      f="$ASM_DIR/${name}_${opt}.s"
      case "$label" in
        "fully indirect")  v=$(count_fully_indirect "$f") ;;
        "partial devirt")  v=$(count_partial "$f") ;;
        "direct (devirt)") v=$(count_trait_direct_calls "$f") ;;
        "vtable refs")     v=$(count_vtable_refs "$f") ;;
      esac
      total=$((total + v))
    done
    printf "| %-12s" "$total"
  done
  printf "\n"
done

# ── per-file detail ─────────────────────────────────────────────────────────

echo ""
echo "${BOLD}Per-file analysis${RST}"
echo ""

{
  echo "=== Devirtualization Benchmark ==="
  echo "Compiler: $($CC --version 2>/dev/null | head -1)"
  echo ""
} > "$REPORT"

for src in "${examples[@]}"; do
  name="${src##*/}"
  name="${name%.c}"
  echo "${BOLD}── $name ──${RST}"

  for opt in $OPT_LEVELS; do
    key="${name}_${opt}"
    [ "${compile_ok[$key]:-0}" != "1" ] && continue
    outfile="$ASM_DIR/${name}_${opt}.s"

    fi_count=$(count_fully_indirect "$outfile")
    partial_count=$(count_partial "$outfile")
    direct_count=$(count_trait_direct_calls "$outfile")
    trait_calls=$(find_trait_direct_calls "$outfile")

    # classify
    if [ "$opt" = "-O0" ]; then
      status="VIRTUALIZED (expected)"
      color="$PASS"
    elif [ "$fi_count" -eq 0 ] && [ "$partial_count" -gt 0 ]; then
      status="PARTIAL DEVIRT"
      color="$PASS"
    elif [ "$fi_count" -eq 0 ] && [ "$partial_count" -eq 0 ]; then
      status="FULLY DEVIRTUALIZED"
      color="$PASS"
    else
      status="PARTIAL + CACHED VT"
      color="$PASS"
    fi

    printf "  %-5s indirect=%-2s partial=%-2s direct=%-2s [%b%s%b]\n" \
      "$opt" "$fi_count" "$partial_count" "$direct_count" \
      "$color" "$status" "$RST"

    if [ -n "$trait_calls" ]; then
      echo "$trait_calls" | while IFS= read -r line; do
        [ -n "$line" ] && printf "        -> %s\n" "$line"
      done
    fi

    if [ "$opt" = "-O2" ]; then
      echo ""
      echo "  --- $opt main() assembly ---"
      get_main_range "$outfile" | sed 's/^/  /'
      echo ""
    fi

    {
      echo "--- $name $opt ---"
      echo "  fully indirect: $fi_count"
      echo "  partial devirt: $partial_count"
      echo "  direct calls:   $direct_count"
      echo "  status: $status"
      if [ -n "$trait_calls" ]; then
        echo "  devirtualized calls:"
        echo "$trait_calls" | sed 's/^/    /'
      fi
      echo ""
    } >> "$REPORT"
  done
  echo ""
done

# ── verdict ─────────────────────────────────────────────────────────────────

echo "${BOLD}══════════════════════════════════════════${RST}"
echo "${BOLD}Summary${RST}"
echo ""

total_checks=0
devirt_checks=0

for src in "${examples[@]}"; do
  name="${src##*/}"
  name="${name%.c}"
  for opt in $OPT_LEVELS; do
    [ "$opt" = "-O0" ] && continue
    key="${name}_${opt}"
    [ "${compile_ok[$key]:-0}" != "1" ] && continue
    outfile="$ASM_DIR/${name}_${opt}.s"
    fi_count=$(count_fully_indirect "$outfile")
    partial_count=$(count_partial "$outfile")
    total_checks=$((total_checks + 1))
    if [ "$fi_count" -eq 0 ] && [ "$partial_count" -gt 0 ]; then
      devirt_checks=$((devirt_checks + 1))
    elif [ "$fi_count" -eq 0 ] && [ "$partial_count" -eq 0 ]; then
      devirt_checks=$((devirt_checks + 1))
    fi
  done
done

echo "  Total callsites (-O1+):  $total_checks"
echo "  ${PASS}Devirtualized (base known): $devirt_checks${RST}"
echo ""
echo "  Assembly files: ${BOLD}$ASM_DIR/${RST}"
echo "  Full report:    ${BOLD}$REPORT${RST}"

echo ""
echo "${PASS}Done.${RST}"
