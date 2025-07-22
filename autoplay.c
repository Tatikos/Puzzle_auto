/**
 * @file autoplay.c
 * @brief Implementation of the automatic Latin Square solver
 * 
 * Contains the main backtracking algorithm and display functions
 * for solving Latin Square puzzles with visual feedback.
 */

#include "autoplay.h"
#include "checks.h"
#include "data.h"
#include <limits.h>

int k = 0;      /**< Step counter for tracking solving progress */
int popnum = 0; /**< Counter for backtrack operations */
int pushnum = 0; /**< Counter for forward operations */

/**
 * @brief Displays the Latin Square in a formatted table with borders
 * @param n Size of the Latin Square (n x n)
 * @param square 2D array containing the current puzzle state
 * 
 * Format:
 * - Uses ASCII art borders with + and - characters
 * - Empty cells show as 0
 * - Negative numbers are displayed in parentheses
 * - Numbers are right-aligned in their cells
 */
void displayLatinSquare(short n, short square[n][n]) {
    for (int i = 0; i < n; i++) {
        printf("+");
        for (int j = 0; j < n; j++) {
            printf("-----+");
        }
        printf("\n");
        for (int j = 0; j < n; j++) {
            if(square[i][j] <0)
                printf("| (%d) ", abs(square[i][j]));
            else
                printf("| %2d  ", square[i][j]);
        }
        printf("|\n");
    }
    printf("+");
    for (int j = 0; j < n; j++) {
        printf("-----+");
    }
    printf("\n");
}

/**
 * @brief Recursively solves the Latin Square using backtracking
 * @param n Size of the Latin Square
 * @param square 2D array representing the puzzle
 * @return true if solution found, false if no solution exists
 * 
 * Algorithm:
 * 1. Find the most constrained empty cell
 * 2. Try each valid number (1 to n) in that cell
 * 3. Recursively attempt to solve the remaining puzzle
 * 4. Backtrack if no solution found with current placement
 * 
 * Uses constraint propagation and displays each step.
 */
bool solve_latin_square(int n, short square[n][n]) {
    int row, col;

    if (!find_most_constrained_cell(n, square, &row, &col)) {
        return true;  
    }
    for (int num = 1; num <= n; num++) {
        if (is_safe(n, row, col, num)) {
            place_number(n, row, col, num, square);
            k++;
            printf("PUSH: STEP %d\n", k);
            displayLatinSquare(n, square);
            if (solve_latin_square(n, square)) {
                return true;
            }
            remove_number(n, row, col, num, square);
            k++;
            printf("POP: STEP %d\n", k);
            displayLatinSquare(n, square);
        }
    }
    return false;
}