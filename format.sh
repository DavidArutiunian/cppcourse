#!/usr/bin/env bash

for f in $(find . -type f ! -path "./CMake*" -name "*.cpp" -or -name "*.hpp");
do
    clang-format -i ${f}
done
