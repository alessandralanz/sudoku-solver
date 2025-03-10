#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdbool.h>
#include <time.h>

#define N 9

//puzzle management functions
void initDefaultPuzzle(int puzzle[N][N]);
void inputPuzzle(int puzzle[N][N]);
void printPuzzle(int puzzle[N][N]);
bool generateRandomPuzzle(int puzzle[N][N], int emptyCells);

//solver functions
bool isSafe(int puzzle[N][N], int row, int col, int num);
bool solveSudoku(int puzzle[N][N]);
bool solveSudokuRandom(int puzzle[N][N]);

//shuffle an array of integers
void shuffle(int *array, int n);

#endif
