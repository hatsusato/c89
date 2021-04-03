#!/bin/bash

set -eu

error() {
  echo "ERROR: $*" >&2
  exit 1
}
usage() {
  cat - <<EOF
USAGE: $0 [-dehsx] <file>
    Compile <file> into LLVM IR

OPTIONS:
    -d  Print AST for debug
    -e  Preprocess only
    -h  Print this help
    -s  Emit LLVM IR by clang
    -x  Execute produced LLVM IR
EOF
  exit
}
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
  local main=$build_dir/main.out
  cd "$top_dir"
  if test -x "$main"; then
    "$main" "$@"
  else
    error "$main not found"
  fi
}
cc() {
  local out=$1.out
  llc | clang -o "$out" -x assembler -
  "$out"
  rm -f "$out"
}
filter() {
  local opts=(-e 's/^; <label>://')
  opts+=(-e '/^[ ]*;/d' -e 's/[ ]*;.*$//')
  opts+=(-e '/^attributes /d' -e 's/ #[0-9]*//')
  opts+=(-e '/^!/d')
  opts+=(-e 's/ common//' -e 's/ dso_local//' -e 's/ signext//')
  sed "${opts[@]}"
}
lines() {
  grep -n "$@" | cut -d: -f1
}
emit() {
  local flags=(-O0 -S -emit-llvm -target x86_64-unknown-linux-gnu)
  local out=$(clang "${flags[@]}" -c "$1" -o - | filter)
  local beg=$(<<<"$out" lines '^target triple' | head -n1)
  local end=$(<<<"$out" lines -v '^$' | tail -n1)
  <<<"$out" sed -n "$beg,$end"p
}

(($#)) || usage
flag=
case "$1" in
  -h) usage;;
  -*) flag="$1"; shift;;
esac
(($#)) || usage
if test -f "$1"; then
  cpp "$1" >/dev/null || error "failed to preprocess: $1"
else
  error "$1 not found"
fi
case "$flag" in
  -d) cpp "$1" | main --debug;;
  -e) cpp "$1";;
  -s) emit "$1";;
  -x) cpp "$1" | main | cc "$1";;
  *) cpp "$1" | main;;
esac
