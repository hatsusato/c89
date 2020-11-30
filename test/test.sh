#!/bin/bash

set -eu

main=./build/main.out

e=$'\e'
bold=$e[1m
green=$e[32m
red=$e[31m
normal=$e[0m

cd $(dirname "$BASH_SOURCE")/..
make &>/dev/null

if ! test -x "$main"; then
  echo "ERROR: $main not found"
  exit 1
fi
for f in $(ls test/src); do
  c=test/src/$f
  ll=test/ans/${f%.c}.ll
  test -f "$c" || continue
  test -f "$ll" || continue
  if diff <("$main" <"$c" 2>/dev/null) "$ll" &>/dev/null; then
    echo "$bold${green}OK$normal: $f"
  else
    echo "$bold${red}NG$normal: $f"
  fi
done
