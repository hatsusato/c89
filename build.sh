#!/bin/bash

set -eu

BUILD_DIR=${BUILD_DIR:-build}
TOP_DIR=$(dirname "$BASH_SOURCE")
cd "$TOP_DIR"

is-parallel() {
  local arg
  for arg; do
    [[ $arg == -j ]] && return 0
  done
  return 1
}
build() {
  mkdir -p "$BUILD_DIR"
  local target_dir=$(cd -P "$BUILD_DIR"; pwd)
  cmake -B "$target_dir" "$@" .
  local opts=(--no-print-directory -C "$BUILD_DIR")
  is-parallel "$@" && opts+=(-j)
  make "${opts[@]}"
}
clean() {
  [[ "$*" != clean ]] && return
  make -C "$BUILD_DIR" clean >/dev/null
  exit
}

clean "$@"
build "$@"
