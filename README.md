# Minishell

Minishell is a simple implementation of a UNIX command line interpreter (shell) written in C.

## Features

- Display a prompt and wait for user input.
- Execute built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Handle basic command execution with arguments.
- Support single and double quotes for command arguments.
- Basic error handling and reporting.

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/AToufik01/minishell_42.git
2. Build the project:
   ```sh
   make
## Usage

1. Run the shell:
   ```sh
   ./minishell
2. Example Commands:
   ```sh
    $ ls |cat |ls -l >file
    $ cat << aa >> file2 | cat << bb >> file2 |cat << cc >>file2
    $ pwd
    $ cd /path/to/somewhere
    $ export MYVAR=value
    $ echo $MYVAR value
    $ unset MYVAR
    $ exit

## Built-in Commands
  ..
