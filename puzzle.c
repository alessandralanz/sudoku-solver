#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

//initialize the puzzle with a default configuration
void initDefaultPuzzle(int puzzle[N][N]) {
    int defaultPuzzle[N][N] = {
        {0, 1, 9, 0, 0, 2, 0, 0, 0},
        {4, 7, 0, 6, 9, 0, 0, 0, 1},
        {0, 0, 0, 4, 0, 0, 0, 9, 0},
        {8, 9, 4, 5, 0, 7, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 1, 9, 5, 8},
        {0, 5, 0, 0, 0, 6, 0, 0, 0},
        {6, 0, 0, 0, 2, 8, 0, 7, 9},
        {0, 0, 0, 1, 0, 0, 8, 6, 0}
    };
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            puzzle[i][j] = defaultPuzzle[i][j];
        }
    }
}

//allow the user to input a custom puzzle
void inputPuzzle(int puzzle[N][N]) {
    int num;
    printf("Enter your puzzle row by row (use 0 for empty cells):\n");
    for (int i = 0; i < N; i++) {
        printf("Row %d: ", i +1);
        for (int j = 0; j < N; j++) {
            while (scanf("%d", &num) != 1 || num < 0 || num > 9){
                //clear invalid input
                printf("Invalid input. Please enter an integer between 0 and 9: ");
                while(getchar() != '\n'); 
            }
            puzzle[i][j] = num;
        }
    }
}

//print the puzzle grid
void printPuzzle(int puzzle[N][N]) {
    for (int i = 0; i < N; i++) {
        if (i % 3 == 0) {
            printf("+-------+-------+-------+\n");
        }
        for (int j = 0; j < N; j++) {
            if (j % 3 == 0) {
                printf("| ");
            }
            //print dot for empty cells or print the number if not empty
            if (puzzle[i][j] == 0) {
                printf(". ");
            } else {
                printf("%d ", puzzle[i][j]);
            }
        }
        printf("|\n");
    }
    printf("+-------+-------+-------+\n");
}

//shuffle an array using Fisher-Yates
void shuffle(int *array, int n){
    for (int i = n - 1; i > 0; i--){
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

//generate a random puzzle
//emptyCells: # of cells to clear for difficulty
bool generateRandomPuzzle(int puzzle[N][N], int emptyCells){
    //intialize with zeros
    for (int i =0; i < N; i++){
        for (int j = 0; j < N; j++){
            puzzle[i][j] = 0;
        }
    }

    //fill the diagonal 3x3 subgrids to reduce complexity (don't interfere with one another)
    for (int i = 0; i < N; i += 3){
        int nums[N] = {1,2,3,4,5,6,7,8,9};
        shuffle(nums, 9);
        int index = 0;
        for (int row = i; row < i + 3; row ++){
            for (int col = i; col < i + 3; col++){
                puzzle[row][col] = nums[index++];
            }
        }
    }

    //randomized solver to fill the rest of the board
    //function similar to solveSudoku but tries numbers in random order
    if (!solveSudokuRandom(puzzle)){
        //printf("Error: Failed to generate a complete puzzle.\n");
        return false; //puzzle generation failed
    }

    //remove cells to create the puzzle
    while (emptyCells > 0){
        int i = rand() % N;
        int j = rand() % N;
        if (puzzle[i][j] != 0){
            puzzle[i][j] = 0;
            emptyCells--;
        }
    }
    return true;
}
