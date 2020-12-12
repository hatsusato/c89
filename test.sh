#!/bin/bash

set -eu

cd $(dirname "$BASH_SOURCE")
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
  "$comp" -S "$target" >/dev/null || exit
  if compare >/dev/null; then
    echo "$bold${green}OK$normal: $1"
  else
    echo "$bold${red}NG$normal: $1"
    test "$diff_flag" && compare -y || :
    return 1
  fi
}

if (($#)); then
  diff_flag=on
else
  for f in $(ls test/); do
    set -- "$@" "${f%.c}"
  done
fi
count=0
for i in "$@"; do
  target=test/$i.c
  test -f "$target" || error "$target not found"
  check "$i" || ((++count))
done
exit $count
