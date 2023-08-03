# Installation

## Pre-built binary

You can download pre-built binary from [GitHub Release](https://github.com/Young-TW/yush/releases).

## Build from source

To build from source, please ensure CMake and C++ compiler installed.

Clone this repository with submodules.

```sh
git clone --recurse-submodules https://github.com/Young-TW/yush.git
```

Then, run the following commands in the directory after cloning this repository.

```sh
cmake . -B build
cmake --build build
```

### Install

```sh
sudo cmake --install build
```