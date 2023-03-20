# Installation

yush have two different ways to install.
1. use precompiled executable
2. build & compile with cmake

you have to choose one to install yush.

## Precompiled executable

1. open [github release page]()
2. download yush executable file
3. put `yush` into $PATH dir

## Build & compile with cmake

- please install yush building dependencies before build.
1. cmake
2. C++ compiler (clang++/g++)
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

install  

```sh
sudo cmake --install build
```

open `yush`  

```sh
yush
```