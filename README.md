# Sudoku Solver

This project is a customizable sudoku solver written in C. It includes:

- A default puzzle setup
- User input for custom puzzles (each number value must be separated by a space and be within the range 1-9 or 0 to denote a blank square)
- Random puzzle generation with difficulty levels (easy, medium, hard, expert)
- A backtracking-based solver
- A terminal interface with formatted output

## Features

- **Default Puzzle:** Load a predefined puzzle.
- **Custom Input:** Enter your own puzzle via the terminal
- **Random Puzzle Generation:** Generate puzzles at various difficulty levels
- **Solver:** Uses a backtracking algorithm to solve puzzles
- **Formatted Output:** The puzzle grid is printed with clear separators

## Installation

To compile the project, make sure you have GCC installed. Then, run:

```bash
gcc puzzle.c sudoku.c -o sudoku_solver
