#!/bin/bash

set -eu

cpp() {
  local flags=(-x c -P -E -)
  flags+=(-Wall -Wextra -Werror -ansi -pedantic)
  cat - "$1" <<EOF | clang "${flags[@]}"
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
  cpp "$TARGET" >/dev/null || error "$TARGET"
  if test "$eflag"; then
    cpp "$TARGET"
  elif test "$sflag"; then
    cpp "$TARGET" | "$main" 2>/dev/null
  elif test "$xflag"; then
    cpp "$TARGET" | "$main" 2>/dev/null | llc | clang -x assembler -
    ./a.out
  else
    cpp "$TARGET" | "$main" >/dev/null
  fi
done
