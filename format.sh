#!/usr/bin/env bash

FORMAT_VER="11"
FORMAT_OPTS="-i -style=file"
TIDY_OPTS="-p . --fix --fix-errors"
COMPILER_OPTS="-fno-builtin -std=gnu90 -Iinclude -Isrc -D_LANGUAGE_C -DNON_MATCHING"

shopt -s globstar

if [ -z `command -v clang-format-${FORMAT_VER}` ]
then
    echo "clang-format-${FORMAT_VER} not found. Exiting."
    exit 1
fi

if (( $# > 0 )); then
    echo "Formatting file(s) $*"
    echo "Running clang-format..."
    clang-format-${FORMAT_VER} ${FORMAT_OPTS} "$@"
    echo "Running clang-tidy..."
    clang-tidy ${TIDY_OPTS} "$@" -- ${COMPILER_OPTS} &> /dev/null
    echo "Adding missing final new lines..."
    sed -i -e '$a\' "$@"
    echo "Done formatting file(s) $*"
    exit
fi

echo "Formatting C files. This will take a bit"
echo "Running clang-format..."
clang-format-${FORMAT_VER} ${FORMAT_OPTS} src/**/*.c
echo "Running clang-tidy..."
clang-tidy ${TIDY_OPTS} src/**/*.c -- ${COMPILER_OPTS} &> /dev/null
echo "Adding missing final new lines..."
find src/ -type f -name "*.c" -exec sed -i -e '$a\' {} \;
find assets/xml/ -type f -name "*.xml" -exec sed -i -e '$a\' {} \;
echo "Done formatting all files."
