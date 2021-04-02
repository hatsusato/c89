#!/bin/bash

set -eu

top_dir=$(dirname "$BASH_SOURCE")
cd -P "$top_dir"
top_dir=$(pwd)
mkdir -p build
cd -P build
cmake "$top_dir" &>/dev/null
make &>/dev/null
cd -P "$top_dir"

error() {
  echo "ERROR: $*"
  exit 1
}
comp() {
  local sh=./compile.sh
  test -x "$sh" || error "$sh not found"
  "$sh" "$1"
}
emit() {
  local sh=./compile.sh
  test -x "$sh" || error "$sh not found"
  "$sh" -s "$1"
}
compare() {
  local target=$1
  shift
  diff "$@" <(emit "$target") <(comp "$target")
}
check() {
  local bold=$'\e[1m'
  local green=$'\e[32m'
  local red=$'\e[31m'
  local normal=$'\e[0m'
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

excludes=()
opts=(-name '*.c')
for f in "${excludes[@]}"; do
  opts+=('!' -name "$f")
done
count=0
for f in $(find test/ "${opts[@]}" | sort); do
  check "$f" || ((++count))
done
exit $count
