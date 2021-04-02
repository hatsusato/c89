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
main() {
  local top_dir=$(dirname "$BASH_SOURCE")
  local build_dir=${BUILD_DIR:-build}
  local main=$top_dir/$build_dir/main.out
  "$main" "$@"
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

for TARGET in "${files[@]}"; do
  cpp "$TARGET" >/dev/null || error "$TARGET"
  if test "$eflag"; then
    cpp "$TARGET"
  elif test "$sflag"; then
    cpp "$TARGET" | main
  elif test "$xflag"; then
    cpp "$TARGET" | main | llc | clang -x assembler -
    ./a.out
  else
    cpp "$TARGET" | main
  fi
done
