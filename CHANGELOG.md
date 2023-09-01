# Changelog
All notable changes to this project will be documented in this file.

## [0.5.2] - 2023-09-02
### Added
- improve `alias`
- `function` command
- input escape
- `getchar` to get input in interactive mode

### Updated
- cmake minimum version to 3.5.0

## [0.5.1] - 2023-08-31
### Added
- `alias` command
- parse ' and " in command line arguments
- $ to use vars in command line arguments

## [0.5.0] - 2023-08-23
### Added
- fork() to execute external commands

### Fixed
- signal will be only send to child process now
- yush will not exit when child process done now

## [0.4.4] - 2023-08-20
### Fixed
- shell broken when .yushrc not exists

### Other
- sync yush version in CMakeLists.txt and main.cpp

## [0.4.3] - 2023-08-06
### Added
- `-i` `--interactive` for interactive mode
- `-c` `--command` for execute single command and exit
- `#` for comment

### Fixed
- remove fmt color flashing
- interactive mode not running by default

## [0.4.2] - 2023-08-04
### Added
- Colors in interactive mode and `ls` command
- `std::cerr`

### Fixed
- sigsegv from parsing command line arguments

## [0.4.1] - 2023-08-04
### Fixed
- Execute `~/.yushrc` file when yush launch

## [0.4.0] - 2023-08-03
### Deleted
- `stream_manager`
- Unnessary bulitin commands

### Added
- fmt to format output

## [0.3.3] - 2023-06-08
### Added
- `main.cpp` cxxopts support

## [0.3.2] - 2023-06-08
### Fixed
- Fix Github Actions workflow

## [0.3.1] - 2023-06-08
### Added
- `cxxopts` to parse command line arguments (not done yet)

## [0.3.0] - 2023-06-07
### Added
- execve() to execute local commands
- signal catch
- remove multiple spaces of input
- get all env vars

## [0.2.0] - 2023-03-21
This version is the first version remove all Windows support.
### Added
- varible_manager
- env var
- home path print as `~` and root as `/`
- color theme
- load commands from env var
- run `.yush` script file
- run `~/.yushrc` when yush launch

## [last windows version] - 2023-03-16
Remove Windows support after this version
### Added
- load commands from env var

## [0.1.0] - 2022-11-12
### Added
- Initial release

[0.5.2]: https://github.com/Young-TW/yush/releases/tag/v0.5.2
[0.5.1]: https://github.com/Young-TW/yush/releases/tag/v0.5.1
[0.5.0]: https://github.com/Young-TW/yush/releases/tag/v0.5.0
[0.4.4]: https://github.com/Young-TW/yush/releases/tag/v0.4.4
[0.4.3]: https://github.com/Young-TW/yush/releases/tag/v0.4.3
[0.4.2]: https://github.com/Young-TW/yush/releases/tag/v0.4.2
[0.4.1]: https://github.com/Young-TW/yush/releases/tag/v0.4.1
[0.4.0]: https://github.com/Young-TW/yush/releases/tag/v0.4.0
[0.3.3]: https://github.com/Young-TW/yush/releases/tag/v0.3.3
[0.3.2]: https://github.com/Young-TW/yush/releases/tag/v0.3.2
[0.3.1]: https://github.com/Young-TW/yush/releases/tag/v0.3.1
[0.3.0]: https://github.com/Young-TW/yush/releases/tag/v0.3.0
[0.2.0]: https://github.com/Young-TW/yush/releases/tag/v0.2
[last windows version]: https://github.com/Young-TW/yush/releases/tag/windows-latest
[0.1.0]: https://github.com/Young-TW/yush/releases/tag/v0.1