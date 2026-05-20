# Write a Simple Shell

This project is an attempt to build my own minimalistic shell in C.

The goal is to understand how a shell works internally, including concepts such as:

- Reading user command
- Parsing commands
- Tokenizing input
- Builtin commands
- Process creation with `fork()`, replacing programs with `exec()` and keeping tabs open on child processes with `wait()`
- Executing commands
- Basic shell architecture

Currently supporting 3 builtin commands:

- `cd`
- `help`
- `exit`

Each command runs in its own separate process as part of understanding process creation and execution.

## How to try it

### 1. Clone the repository

```bash
git clone <repository-url>
cd cwriteashell
```

### 2. Build the project

```bash
make
```

This builds:

```bash
./program
```

### 3. Run the shell

```bash
make run
```

or manually:

```bash
./program
```

### 4. Example commands

```bash
help
cd ..
exit
```

### 5. Clean generated files

```bash
make clean
```