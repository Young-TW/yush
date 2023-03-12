# yush

A simple shell.  

## Commands

- [ ] alias
- [x] cat
- [x] cd
- [x] clear
- [x] cp
- [x] date
- [x] echo
- [x] exit
- [x] help
- [x] la
- [x] ls
- [x] mkdir
- [x] mv
- [x] pwd
- [x] rm
- [x] touch
- [x] whoami

## yush Commands

- [x] set
- [ ] function

## Feature

- [x] varibles
    - [x] `$system`
    - [x] `$theme`
- [ ] user system
- [x] home path print as `~` and root as `/`
- [x] color theme
- [ ] load commands from env var
    - [ ] Windows
    - [x] Linux & MacOS
- [x] run `.yush` script file
- [ ] tab auto fill command

## System support

- [x] Linux
    - [x] Ubuntu 22.04
- [x] MacOS
- [ ] Windows
    - [ ] 10
    - [ ] 11

## Usage

clone the repository

```sh
git clone https://github.com/Young-TW/yush.git

cd yush
```

### install

```sh
cmake . -B build
cd build
make
make install
```