#!/bin/bash

set -eu

print() {
  local opts=(-Wall -Wextra -Werror -ansi -pedantic -x c -P)
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

eflag=
if [[ "$1" == -E ]]; then
  eflag=on
  shift
fi
for arg in "$@"; do
  if test "$eflag"; then
    print "$arg" -Isrc -fsyntax-only
  else
    print "$arg" -Isrc -fsyntax-only >/dev/null
    print "$arg" -Isrc -E | ./main.out
  fi
done
