#!/bin/bash

set -eu

EXCLUDES=()
BUILD_DIR=${BUILD_DIR:-build}
TEST_DIR=${TEST_DIR:-test}
FILES=()
TOP_DIR=$(dirname "$BASH_SOURCE")
cd "$TOP_DIR"

error() {
  echo "ERROR: $*" >&2
  exit 1
}
build() {
  mkdir -p "$BUILD_DIR"
  local target_dir=$(cd -P "$BUILD_DIR"; pwd)
  cmake -B "$target_dir" "$@" .
  make --no-print-directory -C "$target_dir"
}
clean() {
  make -C "$BUILD_DIR" clean >/dev/null
}
tests() {
  local f opts=(-name '*.c')
  for f in "${EXCLUDES[@]}"; do
    opts+=('!' -name "$f")
  done
  while read -r f; do
    FILES+=("$f")
  done < <(find "$TEST_DIR" "${opts[@]}" | sort)
}
compile() {
  local sh=./compile.sh
  if test -x "$sh"; then
    "$sh" "$@"
  else
    error "$sh not found"
  fi
}
compare() {
  local out=1
  if [[ "$1" == -q ]]; then
    exec {out}>/dev/null
  fi
  diff "$1" <(compile -s "$2") <(compile "$2") >&$out
}
print() {
  local e=$'\e['
  local bold=${e}1m
  local color=${e}${1}m
  local normal=${e}0m
  local name=${3#$TEST_DIR}
  echo "$bold$color$2$normal: ${name#/}"
}
check() {
  compile "$1" >/dev/null || exit
  if compare -q "$1"; then
    print 32 OK "$1"
  else
    print 31 NG "$1"
    compare -y "$1"
    return 1
  fi
}
main() {
  local f count=0
  for f in ${FILES[@]}; do
    check "$f" || ((++count))
  done
  exit $count
}

if [[ "$*" == clean && "$*" == "$1" ]]; then
  clean
else
  (build "$@")
  tests
  main
fi
