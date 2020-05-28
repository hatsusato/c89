#!/bin/bash

print() {
  gcc -Isrc -E -P "$1" | ./main.out
}

make main.out &>/dev/null
if (($#)); then
  files=("$@")
else
  files=()
  while read -r f; do
    files+=("$f")
  done < <(find test -name '*.c')
fi
for f in "${files[@]}"; do
  print "$f"
done
