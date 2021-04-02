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
color() {
  local bold=$'\e['1m
  local color=$'\e['"$1"m
  local normal=$'\e['0m
  echo "$bold$color$2$normal$3"
}
check() {
  local name=${1##*/}
  name=${name%.c}
  compile "$1" >/dev/null || exit
  if compare -q "$1"; then
    color 32 OK ": $name"
  else
    color 31 NG ": $name"
    compare -y "$1"
    return 1
  fi
}

build
count=0
for f in $(tests); do
  check "$f" || ((++count))
done
exit $count
