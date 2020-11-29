#!/bin/bash

cflags=(-O0 -S -emit-llvm)

for f in "$@"; do
  l=${f%.c}.ll
  clang "${cflags[@]}" -c "$f" -o "$l"
  cat "$l"
done
