#!/bin/bash


number() {
  cut -d: -f1 | tail -n1
}
filter() {
  local opts=(-v -e '^[!;]' -e '^attributes')
  grep "${opts[@]}" | sed -e 's/ #[0-9]* / /'
}

cflags=(-O0 -S -emit-llvm)
for f in "$@"; do
  l=${f%.c}.ll
  out=$(clang "${cflags[@]}" -c "$f" -o - | filter)
  beg=$(<<<$out grep -n '^target triple' | number)
  end=$(<<<$out grep -n -v ^$ | number)
  <<<$out sed -n "$beg,$end"p
done
