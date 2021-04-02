#!/bin/bash

set -eu

EXCLUDES=()

build() {
  local top_dir=$(dirname "$BASH_SOURCE")
  local build_dir=${BUILD_DIR:-build}
  cd -P "$top_dir"
  mkdir -p "$build_dir"
  local target_dir=$(cd -P "$build_dir" ; pwd)
  cmake -B "$target_dir" "$@" .
  make -C "$target_dir" --no-print-directory
}
tests() {
  local f opts=(-name '*.c')
  for f in "${EXCLUDES[@]}"; do
    opts+=('!' -name "$f")
  done
  find test/ "${opts[@]}" | sort
}
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
color() {
  local bold=$'\e['1m
  local color=$'\e['"$1"m
  local normal=$'\e['0m
  echo "$bold$color$2$normal$3"
}
check() {
  local name=${1##*/}
  name=${name%.c}
  comp "$1" >/dev/null || exit
  if compare "$1" >/dev/null; then
    color 32 OK ": $name"
  else
    color 31 NG ": $name"
    compare "$1" -y
    return 1
  fi
}

build
count=0
for f in $(tests); do
  check "$f" || ((++count))
done
exit $count
