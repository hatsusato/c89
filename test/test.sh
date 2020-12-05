#!/bin/bash

set -eu

cd $(dirname "$BASH_SOURCE")/..
make &>/dev/null

comp=./compile.sh
emit=./emit-llvm.sh
target=
diff_flag=

error() {
  echo "ERROR: $*"
  exit 1
}

test -x "$comp" || error "$comp not found"
test -x "$emit" || error "$emit not found"

compare() {
  diff "$@" <("$emit" "$target") <("$comp" -S "$target")
}
check() {
  local e=$'\e'
  local bold=$e[1m
  local green=$e[32m
  local red=$e[31m
  local normal=$e[0m
  local ret=0
  compare || ret=$?
  case $ret in
    0) echo "$bold${green}OK$normal: $1";;
    1) echo "$bold${red}NG$normal: $1";;
    *) exit $ret;;
  esac
  if test "$diff_flag"; then
    if (($ret)); then
      compare -u || :
    else
      "$comp" -S "$target"
    fi
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
  target=test/src/$i.c
  test -f "$target" || error "$target not found"
  check "$i"
done
