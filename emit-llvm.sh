#!/bin/bash

cflags=(-O0 -S -emit-llvm)

for f in "$@"; do
  clang "${cflags[@]}" -c "$f" -o "${f%.c}.ll"
done
