#!/bin/bash

set -eu

main=./build/main.out

compare() {
  local e=$'\e'
  local bold=$e[1m
  local green=$e[32m
  local red=$e[31m
  local normal=$e[0m
  local c=test/src/$1.c
  local ll=test/ans/$1.ll
  test -f "$c" || continue
  test -f "$ll" || continue
  if diff <("$main" <"$c" 2>/dev/null) "$ll" &>/dev/null; then
    echo "$bold${green}OK$normal: $i"
  else
    echo "$bold${red}NG$normal: $i"
  fi
}

cd $(dirname "$BASH_SOURCE")/..
make &>/dev/null

if ! test -x "$main"; then
  echo "ERROR: $main not found"
  exit 1
fi
if (($# == 0)); then
  for f in $(ls test/src); do
    set -- "$@" "${f%.c}"
  done
fi
for i in "$@"; do
  compare "$i"
done
