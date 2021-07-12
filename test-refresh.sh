#!/bin/bash

set -eu

quiet=

filter-make() {
  if [[ $quiet ]]; then
    cat - >/dev/null
  else
    cat -
  fi
}
memcheck() {
  local out grep
  if [[ $quiet ]]; then
    grep=(grep -e exit)
  else
    grep=(grep -e '.*')
  fi
  (
    exec {out}>&1
    valgrind --tool=memcheck --log-fd=$out ./build/main.out "$@"
  ) | "${grep[@]}"
}

[[  ${1-} == -q  ]] && quiet=on
cd "${BASH_SOURCE%/*}"
make -j --no-print-directory -C build | filter-make
memcheck --unittest
memcheck <test/01.c
