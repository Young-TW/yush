#!/usr/bin/env bash

# check git is installed
if ! [ -x "$(command -v git)" ]; then
  echo 'Error: git is not installed.' >&2
  exit 1
fi

# check cmake is installed
if ! [ -x "$(command -v cmake)" ]; then
  echo 'Error: cmake is not installed.' >&2
  exit 1
fi

# check ninja is installed
if ! [ -x "$(command -v ninja)" ]; then
  echo 'Error: ninja is not installed.' >&2
  exit 1
fi

# check clang is installed
if ! [ -x "$(command -v clang)" ]; then
  echo 'Error: clang is not installed.' >&2
  exit 1
fi

echo "start Build"
git submodule update --init --recursive
cmake -B build
cmake --build build --config RELEASE
cmake --install build --config RELEASE
echo "yush installed successfully"
