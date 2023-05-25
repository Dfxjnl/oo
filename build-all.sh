#!/usr/bin/env sh
cmake --workflow --preset=gcc-debug
cmake --workflow --preset=gcc-relwithdebinfo
cmake --workflow --preset=gcc-release
cmake --workflow --preset=gcc-sanitize
cmake --workflow --preset=clang-debug
cmake --workflow --preset=clang-relwithdebinfo
cmake --workflow --preset=clang-release
cmake --workflow --preset=clang-sanitize
cmake --workflow --preset=static-analyzers
cmake --workflow --preset=include-what-you-use
