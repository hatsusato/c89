#!/bin/bash

set -eu

main=./build/main.out
diff_flag=

compare() {
  local e=$'\e'
  local bold=$e[1m
  local green=$e[32m
  local red=$e[31m
  local normal=$e[0m
  local c=test/src/$1.c
  local ll=test/ans/$1.ll
  test -f "$c" || return
  test -f "$ll" || return
  if diff "$ll" <("$main" <"$c" 2>/dev/null) &>/dev/null; then
    echo "$bold${green}OK$normal: $i"
  else
    echo "$bold${red}NG$normal: $i"
    if test "$diff_flag"; then
      diff -u "$ll" <("$main" <"$c" 2>/dev/null) || :
    fi
  fi
}

cd $(dirname "$BASH_SOURCE")/..
make &>/dev/null

if ! test -x "$main"; then
  echo "ERROR: $main not found"
  exit 1
fi
if (($#)); then
  diff_flag=on
else
  for f in $(ls test/src); do
    set -- "$@" "${f%.c}"
  done
fi
for i in "$@"; do
  compare "$i"
done
