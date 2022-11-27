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

### Other commands

- [ ] finger
- [ ] man
- [ ] whatis
- [ ] which
- [ ] whereis

## Feature

- [x] varibles
    - [x] $system
- [x] user system
- [x] home path print as `~` and root as `/`
- [x] color theme
- [x] load commands from env var
    - [x] Windows
    - [x] Linux & MacOS
- [ ] tab auto fill command
- [ ] arrow (select past commands)
    - [x] vector (to save past commands)
    - [ ] up/down switch past commands
    - [ ] left/right switch input place

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