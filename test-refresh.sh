#!/bin/bash

set -eu

filter() {
  if [[ $quiet ]]; then
    cat - >/dev/null
  else
    cat -
  fi
}
memcheck() {
  valgrind --tool=memcheck --leak-check=full --log-fd=2 ./build/main.out "$@" | filter
}
main() {
  local quiet=
  [[ ${1-} == -q ]] && quiet=on
  cd "${BASH_SOURCE%/*}"
  make -j --no-print-directory -C build | filter
  memcheck --unittest
  memcheck <test/01.c
  diff <(./build/main.out <test/01.c) test/01.c.ast
}

main "$@"
