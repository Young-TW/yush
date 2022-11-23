# yush

A simple shell.  

## Commands

- [ ] alias
- [ ] cat
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
- [ ] su
- [x] time
- [x] touch
- [ ] useradd
- [ ] userdel
- [x] whoami

### maybe will make
- [ ] finger
- [ ] man
- [ ] whatis
- [ ] which
- [ ] whereis

## Feature

- [ ] arrow (select past commands)
    - [x] vector (to save past commands)
- [x] varibles
    - [x] $system
- [x] user system
- [x] home path print as `~` and root as `/`
- [x] color theme
- [ ] copy & paste shortcut key
- [ ] load commands from env var
    - [ ] Windows
    - [ ] Linux & MacOS

## Todo

- [ ] arrow switch past commands
- [ ] arrow switch input place
- [ ] cat command

## System support

- [x] Linux (Ubuntu 22.04)
- [x] MacOS
- [x] Windows 10

## Usage

clone the repository  

```sh
git clone https://github.com/Young-TW/yush.git
```

build  

```sh
cd yush

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