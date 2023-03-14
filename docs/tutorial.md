# Tutorial

## What is yush?

Young's shell (`yush`) is a project that built by [Young](https://github.com/Young-TW).  

## Why yush?

`yush` is also a growing shell project using modern C++23 standard and easy to modify.  

## Start using yush

- please install yush building dependencies before build.
1. cmake
2. C++ compiler (clang++/g++/visual studio build tools)
3. build tools (makefile/ninja)
4. git (to clone the repo)

clone the project  

```sh
git clone https://github.com/Young-TW/yush.git
cd yush
```

build  

```sh
cmake . -B build
cmake --build build --config RELEASE
```

install (makefile)  

```sh
cd build
make install
```

open `yush`

```sh
yush
```