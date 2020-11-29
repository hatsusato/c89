#!/bin/bash

set -eu

MAIN_DIR=build

TARGET=
FLAGS=()
print() {
  local opts=("$@" "${FLAGS[@]}")
  opts+=(-Wall -Wextra -Werror -ansi -pedantic)
  opts+=(-x c -P -E -)
  cat - "$TARGET" <<EOF | gcc "${opts[@]}"
#define __attribute__(x)
#define __asm__(x)
#define __extension__
#define __inline
#define __restrict
EOF
}
error() {
  echo ERROR: "$@" >&2
  exit 1
}

files=()
eflag=
sflag=
xflag=
for arg in "$@"; do
  case "$arg" in
    -E) eflag=on;;
    -S) sflag=on;;
    -X) xflag=on;;
    -*) FLAGS+=("$arg");;
    *) files+=("$arg");;
  esac
done

main=${MAIN_DIR-.}/main.out
for TARGET in "${files[@]}"; do
  print -fsyntax-only >/dev/null || error "$TARGET"
  if test "$eflag"; then
    print
  elif test "$sflag"; then
    print | "$main" 2>/dev/null
  elif test "$xflag"; then
    print | "$main" 2>/dev/null | llc | clang -x assembler -
    ./a.out
  else
    print | "$main" >/dev/null
  fi
done
