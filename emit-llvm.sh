#!/bin/bash

filter() {
  local opts=(-e 's/^; <label>://')
  opts+=(-e '/^[ ]*;/d' -e 's/[ ]*;.*$//')
  opts+=(-e '/^attributes /d' -e 's/ #[0-9]*//')
  opts+=(-e '/^!/d')
  opts+=(-e 's/ dso_local//' -e 's/ common//')
  sed "${opts[@]}"
}
number() {
  cut -d: -f1 | tail -n1
}

cflags=(-O0 -S -emit-llvm -target x86_64-unknown-linux-gnu)
for f in "$@"; do
  out=$(clang "${cflags[@]}" -c "$f" -o - | filter)
  beg=$(<<<"$out" grep -n '^target triple' | number)
  end=$(<<<"$out" grep -n -v '^$' | number)
  <<<"$out" sed -n "$beg,$end"p
done
