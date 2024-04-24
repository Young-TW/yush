# Developer Docs

This is the developer documentation for the `yush` project.

If you are looking for the user documentation, please see the [Tutorial](./tutorial.md).

## Getting Started

clone this repository and deps.

```sh
git clone --recurse-submodules https://github.com/Young-TW/yush.git
```

build yush with cmake.

```sh
cmake . -B build
cmake --build build
```

## Code architecture

yush uses a `Shell` class to manage the whole shell.

`Shell` class is a singleton class, which means there is only one instance of `Shell` class in the whole program.

`Shell` class has some built-in commands, such as `alias`, `cd`, `echo`, `pwd`, `set`, etc.
Built-in commands are named in the format of `cmd_<command_name>` in `Shell` class.

`Shell` class also has a `VariableManager` class to manage variables from env.

Any program returns a value to the shell, which is called `runtime_status`.

`Command` class is the base class for user input commands(from interactive shell or script file).
