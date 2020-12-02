#!/bin/bash

set -eu

cd $(dirname "$BASH_SOURCE")/..
make &>/dev/null

main=./build/main.out
emit=./emit-llvm.sh
diff_flag=

if ! test -x "$main"; then
  echo "ERROR: $main not found"
  exit 1
fi
if ! test -x "$emit"; then
  echo "ERROR: $emit not found"
  exit 1
fi

compare() {
  local c=test/src/$1.c
  local ll=test/ans/$1.ll
  shift
  if ! test -f "$c"; then
    echo "ERROR: $c not found"
    exit 1
  fi
  if test -f "$ll"; then
    diff "$@" "$ll" <("$main" <"$c" 2>/dev/null)
  else
    diff "$@" <("$emit" "$c") <("$main" <"$c" 2>/dev/null)
  fi
}
check() {
  local e=$'\e'
  local bold=$e[1m
  local green=$e[32m
  local red=$e[31m
  local normal=$e[0m
  local ret=0
  if compare "$1"; then
    echo "$bold${green}OK$normal: $i"
  else
    echo "$bold${red}NG$normal: $i"
    test "$diff_flag" && compare "$c" -u
  fi
}

if (($#)); then
  diff_flag=on
else
  for f in $(ls test/src); do
    set -- "$@" "${f%.c}"
  done
fi
for i in "$@"; do
  check "$i" || :
done
