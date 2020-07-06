#!/bin/bash

print() {
  local opts=(-Wall -Wextra -ansi -pedantic -x c -E -P -)
  local target="$1"
  shift
  cat - "$target" <<EOF | gcc "$@" "${opts[@]}"
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
    print "$arg" -Isrc
  else
    print "$arg" -Isrc -fsyntax-only >/dev/null || exit $?
    print "$arg" -Isrc | ./main.out
  fi
done
