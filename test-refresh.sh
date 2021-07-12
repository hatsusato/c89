#!/bin/bash

set -eu

make -j --no-print-directory -C build
valgrind ./build/main.out --unittest
