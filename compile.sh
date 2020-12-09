#!/bin/bash

set -eu

TARGET=
FLAGS=(-x c -P -E -)
FLAGS+=(-Wall -Wextra -Werror -ansi -pedantic)
print() {
  cat - "$TARGET" <<EOF | clang "${FLAGS[@]}"
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

main=${MAIN_DIR-./build}/main.out
for TARGET in "${files[@]}"; do
  print >/dev/null || error "$TARGET"
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
