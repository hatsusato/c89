#!/bin/bash

set -eu

tests() {
  local f opts=(-name '*.c') x=excludes.txt
  if test -f "$x"; then
    while read -r f; do
      opts+=('!' -name "$f")
    done <$x
  fi
  find "$TEST_DIR" "${opts[@]}" | sort
}
compare() {
  local out=1
  if [[ $opt == -q ]]; then
    exec {out}>/dev/null
  fi
  diff -W 80 "$opt" <(./compile.sh -s "$1") <(./compile.sh "$1") >&$out
}
print() {
  local e=$'\e['
  local bold=${e}1m
  local color=${e}${1}m
  local normal=${e}0m
  local name=${3#$TEST_DIR}
  echo "$bold$color$2$normal: ${name#/}" >&2
}
check() {
  local opt
  ./compile.sh -s "$1" >/dev/null || exit
  if opt=-q compare "$1"; then
    print 32 PASS "$1"
  else
    print 31 FAIL "$1"
    opt=-y compare "$1"
    return 1
  fi
}
memcheck() {
  local out main=$BUILD_DIR/main.out
  exec {out}>&1
  local opts=(--tool=memcheck --log-fd=$out "$main")
  valgrind "${opts[@]}" >/dev/null
}
verify() {
  local msg=$(./compile.sh -e "$1" | memcheck)
  local leak=$(<<<"$msg" grep exit | cut -d: -f2)
  local zero=' 0 bytes in 0 blocks'
  if [[ "$leak" != "$zero" ]]; then
    print 31 LEAK "$leak"
  fi
}
enabled() {
  if [[ -v DISABLE_VALGRIND ]]; then
    return 1
  else
    which valgrind >/dev/null || return
  fi
}
main() {
  local f count=0
  while read -r f; do
    check "$f" || ((++count))
    enabled && verify "$f"
  done
  exit $count
}

[[ -v BUILD_DIR ]] || ./build.sh
BUILD_DIR=${BUILD_DIR:-build}
TEST_DIR=${TEST_DIR:-test}
TOP_DIR=$(dirname "$BASH_SOURCE")
cd "$TOP_DIR"
tests | main
