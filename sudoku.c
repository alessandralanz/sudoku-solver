#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"

//check if it's safe to place 'num' in the given cell
bool isSafe(int puzzle[N][N], int row, int col, int num) {
    // Check the row and column for duplicates
    for (int x = 0; x < N; x++) {
        if (puzzle[row][x] == num || puzzle[x][col] == num)
            return false;
    }
    //check the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}

//solve the Sudoku puzzle using backtracking
bool solveSudoku(int puzzle[N][N]) {
    int row, col;
    bool foundEmpty = false;
    
    //find an empty cell
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (puzzle[row][col] == 0) {
                foundEmpty = true;
                goto FIND_EMPTY;
            }
        }
    }
FIND_EMPTY:
    //if no empty cell is found, the puzzle is solved
    if (!foundEmpty)
        return true;
    
    //try placing numbers 1 to 9 in the empty cell
    for (int num = 1; num <= 9; num++) {
        if (isSafe(puzzle, row, col, num)) {
            puzzle[row][col] = num;
            
            if (solveSudoku(puzzle))
                return true;
            
            //backtracking
            puzzle[row][col] = 0;
        }
    }
    return false; //trigger backtracking
}

//randomized backtracking solver for puzzle generation
bool solveSudokuRandom(int puzzle[N][N]){
    int row, col;
    bool emptyFound = false;
    for (row = 0; row < N; row++){
        for(col = 0; col < N; col++){
            if (puzzle[row][col] == 0){
                emptyFound = true;
                goto FIND_EMPTY_RANDOM;
            }
        }
    }
FIND_EMPTY_RANDOM:
    if (!emptyFound){
        return true;
    }

    int nums[N];
    for (int i = 0; i < N; i++){
        nums[i] = i + 1;
    }
    shuffle(nums, N);

    for (int i = 0; i < N; i++){
        int num = nums[i];
        if (isSafe(puzzle, row, col, num)){
            puzzle[row][col] = num;
            if (solveSudokuRandom(puzzle)){
                return true;
            }
            puzzle[row][col] = 0;
        }
    }
    return false;
}

int main() {
    int puzzle[N][N]; //stack-allocated puzzle array
    int choice;
    int emptyCells = 0;

    //seed random number generator for puzzle generation
    srand(time(NULL));

    //menu
    printf("Welcome to the Sudoku Solver!\n");
    printf("Please choose an option:\n");
    printf("1) Use default puzzle\n");
    printf("2) Enter your own puzzle\n");
    printf("3) Generate a random puzzle\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    
   switch(choice){
        case 1:
            initDefaultPuzzle(puzzle);
            break;
        case 2:
            inputPuzzle(puzzle);
            break;
        case 3: {
            int difficulty;
            printf("Choose your difficulty level:\n");
            printf("1) Easy \n2) Medium\n3) Hard\n4) Expert\n");
            printf("Your choice: ");
            scanf("%d", &difficulty);
            switch(difficulty){
                case 1: emptyCells = 30; break; //easy
                case 2: emptyCells = 40; break; //medium
                case 3: emptyCells = 50; break; //hard
                case 4: emptyCells = 60; break; //expert
                default:
                    printf("Invalid diffculty. Defaulting to Easy.\n");
                    emptyCells = 30;
                    break;
            }
            if (!generateRandomPuzzle(puzzle, emptyCells)){
                printf("Error: Failed to generate a complete puzzle.\n");
                return 1;
            }
            break;
        }
        default:
            printf("Invalid choice. Using default puzzle.\n");
            initDefaultPuzzle(puzzle);
            break;
   }
    
    printf("\nPuzzle before solving:\n");
    printPuzzle(puzzle);
    
    if (solveSudoku(puzzle)) {
        printf("\nPuzzle solved:\n");
        printPuzzle(puzzle);
    } else {
        printf("\nNo solution exists for the given puzzle.\n");
    }
    
    return 0;
}
