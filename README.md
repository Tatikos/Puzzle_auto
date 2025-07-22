# Puzzle_auto

# Latin Square Solver

A C program that automatically solves Latin Square puzzles using backtracking with constraint propagation.

## What is a Latin Square?

A Latin Square is an n×n grid filled with n different symbols, each occurring exactly once in each row and exactly once in each column.

## Features

- Reads Latin Square puzzles from text files
- Interactive confirmation prompt before solving
- Visual step-by-step solving process with PUSH/POP operations
- Detects unsolvable puzzles
- Uses constraint propagation for efficient solving
- Saves solved puzzles to output files

## Usage

```bash
make
./latin_square_game input.txt
```

## Input Format

First line: size `n`
Next `n` lines: `n` numbers each (0 for empty cells, 1-n for filled cells)

Example:
```
4
1 0 0 4
0 4 0 0
0 0 4 0
4 0 0 2
```

## Files

- `main.c` - Program entry point and file handling
- `autoplay.c` - Backtracking solver implementation
- `checks.c` - Constraint checking and validation
- `data.c` - File I/O operations
- `Makefile` - Build configuration