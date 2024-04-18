# MiniShell

## Description:

MiniShell is a Unix shell implementation developed as part of the 42 Cursus curriculum. It provides a command-line interface to interact with the operating system, supporting various features such as command execution, environment variable management, redirection, pipes, and built-in commands.

## Features:

- **Prompt**: MiniShell displays a prompt when waiting for a new command, indicating readiness to accept user input.
- **History**: It maintains a working history of commands entered by the user, allowing navigation through previous commands.
- **Command Execution**: MiniShell searches and launches the appropriate executable based on the PATH variable or provided path.
- **Quoting**: Handles single and double quotes to prevent interpretation of metacharacters, with exceptions for double quotes allowing variable expansion.
- **Redirections**: Supports input/output redirection using `<`, `>`, `<<`, and `>>` symbols.
- **Pipes**: Implements piping of command outputs using the `|` character, connecting the output of one command to the input of the next.
- **Environment Variables**: Handles environment variables, expanding them to their respective values when encountered.
- **Exit Status**: Provides expansion for `$?`, which represents the exit status of the most recently executed foreground pipeline.
- **Signal Handling**: Handles signals like ctrl-C, ctrl-D, and ctrl-\ in interactive mode as per standard shell behavior.
- **Built-in Commands**: Implements built-in commands including `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Logical Operators**: Supports `&&` and `||` operators with parenthesis for prioritization.
- **Wildcard Expansion**: Enables wildcard `*` functionality for file matching in the current working directory.
