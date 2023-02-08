# yush

A simple shell.  

## Commands

- [ ] alias
- [x] cat
- [x] cd (basic)
- [x] clear
- [x] date
- [x] echo
- [x] exit
- [x] help
- [x] la
- [x] ls
- [x] mkdir
- [x] pwd
- [ ] rm
- [x] time
- [x] touch
- [x] whoami

### Other commands

- [ ] finger
- [ ] man
- [ ] whatis
- [ ] which
- [ ] whereis

## Feature

- [x] varibles
    - [x] `$system`
    - [x] `$theme`
- [x] user system
- [x] home path print as `~` and root as `/`
- [x] color theme
- [x] load commands from env var
    - [x] Windows
    - [x] Linux & MacOS
- [ ] run `.yush` script file
- [ ] tab auto fill command

## System support

- [x] Linux (Ubuntu 22.04)
- [x] MacOS
- [x] Windows 10

## Usage

clone the repository

```sh
git clone https://github.com/Young-TW/yush.git

cd yush
```

### build only

```sh
mkdir build

cd build

cmake ..
```

### build & install to path

- Windows

```ps1
./install.ps1
```

- Linux & MacOS

```sh
sudo bash ./install.sh
```