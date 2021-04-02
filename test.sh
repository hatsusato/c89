#!/bin/bash

set -eu

EXCLUDES=()
FILES=()

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
  while read -r f; do
    FILES+=("$f")
  done < <(find test/ "${opts[@]}" | sort)
}
error() {
  echo "ERROR: $*"
  exit 1
}
compile() {
  local top_dir=$(dirname "$BASH_SOURCE")
  local sh=$top_dir/compile.sh
  if test -x "$sh"; then
    "$sh" "$@"
  else
    echo "ERROR: $sh not found" >&2
    exit 1
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
  local name=${3##*/}
  echo "$bold$color$2$normal: ${name%.c}"
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
  tests
  local f count=0
  for f in ${FILES[@]}; do
    check "$f" || ((++count))
  done
  exit $count
}

build
main
