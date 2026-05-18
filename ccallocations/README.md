# ccallocations

This project is an attempt to build my own versions of `malloc`, `calloc`, `realloc`, and `free` in C.

The goal is to understand how dynamic memory allocation works internally, including concepts such as:

- Heap management
- Metadata headers
- Linked lists
- Memory reuse
- Block splitting and merging
- Alignment

## How to try it

### 1. Clone the repository

```bash
git clone <repository-url>
cd ccallocations
```

### 2. Build the project

```bash
make
```

This builds:

```bash
./program
```

### 3. Run the program

```bash
make run
```

### 4. Clean generated files

```bash
make clean
```