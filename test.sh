#!/bin/bash

set -eu

cd $(dirname "$BASH_SOURCE")
make &>/dev/null

error() {
  echo "ERROR: $*"
  exit 1
}
comp() {
  local sh=./compile.sh
  test -x "$sh" || error "$sh not found"
  "$sh" -S "$1"
}
emit() {
  local sh=./emit-llvm.sh
  test -x "$sh" || error "$sh not found"
  "$sh" "$1"
}
compare() {
  local target=$1
  shift
  diff "$@" <(emit "$target") <(comp "$target")
}
check() {
  local e=$'\e'
  local bold=$e[1m
  local green=$e[32m
  local red=$e[31m
  local normal=$e[0m
  local name=${1##*/}
  name=${name%.c}
  comp "$1" >/dev/null || exit
  if compare "$1" >/dev/null; then
    echo "$bold${green}OK$normal: $name"
  else
    echo "$bold${red}NG$normal: $name"
    compare "$1" -y
    return 1
  fi
}

files=()
if (($#)); then
  for i in "$@"; do
    files+=("test/$i.c")
  done
else
  for f in $(find test/ -name '*.c' | sort); do
    files+=("$f")
  done
fi
count=0
for f in "${files[@]}"; do
  test -f "$f" || error "$f not found"
  check "$f" || ((++count))
done
exit $count
