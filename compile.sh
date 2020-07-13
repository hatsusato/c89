#!/bin/bash

set -eu

print() {
  local opts=(-Wall -Wextra -Werror -ansi -pedantic -x c)
  local target="$1"
  shift
  cat - "$target" <<EOF | gcc "$@" "${opts[@]}" -
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
check() {
  print "$1" -Isrc -fsyntax-only >/dev/null || error "$1"
}
compile() {
  print "$1" -Isrc -E
}

eflag=
if [[ "$1" == -E ]]; then
  eflag=on
  shift
fi
for arg in "$@"; do
  check "$arg"
  if test "$eflag"; then
    compile "$arg"
  else
    compile "$arg" | ./main.out
  fi
done
