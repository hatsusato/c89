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
cc() {
  local out=$1.out
  llc | clang -o "$out" -x assembler -
  "$out"
  rm -f "$out"
}
error() {
  echo "ERROR: $@" >&2
  exit 1
}

flag=
if [[ "$1" == -* ]]; then
  flag="$1"
  shift
fi
cpp "$1" >/dev/null || error "$1"
case "$flag" in
  -e) cpp "$1";;
  -d) cpp "$1" | main --debug;;
  -x) cpp "$1" | main | cc "$1";;
  *) cpp "$1" | main;;
esac
