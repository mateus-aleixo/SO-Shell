# SO-Shell

SO-Shell is a minimalistic shell implemented in the C programming language. It provides a command-line interface where users can interact with the shell, execute commands, and perform various operations.

## Features

- Basic command execution: Execute commands and programs from the shell.
- Input/output redirection: Redirect input/output streams to/from files.
- Pipeline support: Connect multiple commands together using pipes.
- File operations: Perform basic file operations such as copying, moving, and deleting files.
- Customizable prompt: Customize the shell prompt to suit your preferences.

## Getting Started

To get started with SO-Shell, follow these steps:

1. Clone the repository:
git clone https://github.com/mateus-aleixo/SO-Shell.git

2. Build the project:
cd SO-Shell
make

3. Run the shell:
./soshell

## Usage

Once you have the shell running, you can enter commands and interact with it. Here are a few examples:

- Execute a command:
$ls

- Redirect input from a file:
$ sort < input.txt

- Redirect output to a file:
$ ls > output.txt

- Use pipelines to connect multiple commands:
$ cat input.txt | grep "pattern" | sort | uniq
