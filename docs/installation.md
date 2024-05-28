# Installation

## Pre-built binary

You can download pre-built binary from [GitHub Release](https://github.com/Young-TW/yush/releases).

## Build from source

To build from source, please ensure CMake and C++ compiler installed (may require make or ninja).

Here is a script to install yush from source:

```sh
curl https://raw.githubusercontent.com/Young-TW/yush/main/script/install.sh | bash
```

### Clone

Clone this repository with submodules.

```sh
git clone --recurse-submodules https://github.com/Young-TW/yush.git
```

### Dependencies

If you use Ubuntu, you can install dependencies with the following command.

```sh
sudo apt install -y clang build-essential cmake
```

### Build

Build yush with cmake.

We use clang++ as default compiler, but you can also use g++.
If you want to use g++, please change `CMAKE_CXX_COMPILER` to `g++` in `CMakeLists.txt`.

```sh
cmake . -B build
cmake --build build
```

### Install

If you want to install yush, you should download pre-built binary or build from source first.

Then, run the following command to install yush.

```sh
sudo cmake --install build
```
