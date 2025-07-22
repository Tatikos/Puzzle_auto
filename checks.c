/**
 * @file checks.c
 * @brief Implementation of constraint checking and validation functions
 * 
 * Implements the core logic for validating Latin Square constraints
 * using bitmasks for efficient row and column tracking.
 */

#include "checks.h"
#include "autoplay.h"
#include <limits.h>
#include <string.h>

int row_mask[9] = {0}; /**< Bitmasks for tracking numbers in each row */
int col_mask[9] = {0}; /**< Bitmasks for tracking numbers in each column */

/**
 * @brief Initializes constraint masks from the current puzzle state
 * @param n Size of the Latin Square
 * @param square 2D array representing the puzzle
 * @return true if initialization successful and puzzle is valid, false otherwise
 * 
 * This function validates the initial puzzle state and sets up bitmasks
 * for efficient constraint checking during solving.
 */
bool initialize(short n, short square[n][n]) {
    memset(row_mask, 0, sizeof(row_mask));
    memset(col_mask, 0, sizeof(col_mask));

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (square[r][c] != 0) {
                int num = abs(square[r][c]);
                int bit = 1 << (num - 1);
                if ((row_mask[r] & bit) != 0) {
                    printf("Error: Duplicate number %d in row %d.\n", num, r + 1);
                    return false;
                }
                row_mask[r] |= bit;
                if ((col_mask[c] & bit) != 0) {
                    printf("Error: Duplicate number %d in column %d.\n", num, c + 1);
                    return false;
                }
                col_mask[c] |= bit;
            }
        }
    }
    return true;
}

/**
 * @brief Utility function to check if a character exists in a string
 * @param str String to search in
 * @param ch Character to search for
 * @return 1 if character found, 0 otherwise
 */
int containsChar(const char *str, char ch) {
    while (*str != '\0') {
        if (*str == ch) {
            return 1;
        }
        str++;
    }
    return 0;
}

/**
 * @brief Finds the empty cell with minimum valid placement options
 * @param n Size of the Latin Square
 * @param square Current state of the puzzle
 * @param row Pointer to store the row of most constrained cell
 * @param col Pointer to store the column of most constrained cell
 * @return true if empty cell found, false if puzzle is complete
 * 
 * Uses the Most Constrained Variable heuristic to improve solving efficiency.
 */
bool find_most_constrained_cell(int n, short square[n][n], int *row, int *col) {
    int min_options = INT_MAX;
    bool found_empty_cell = false;

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (square[r][c] == 0) {
                found_empty_cell = true;
                int options = 0;
                for (int num = 1; num <= n; num++) {
                    if (is_safe(n, r, c, num)) {
                        options++;
                    }
                }

                if (options < min_options) {
                    min_options = options;
                    *row = r;
                    *col = c;
                }
            }
        }
    }

    return found_empty_cell;
}

/**
 * @brief Checks if placing a number at a position violates constraints
 * @param n Size of the Latin Square
 * @param row Row position (0-based)
 * @param col Column position (0-based)
 * @param num Number to check (1 to n)
 * @return true if placement is safe, false if it violates constraints
 */
bool is_safe(int n, int row, int col, int num) {
    int bit = 1 << (num - 1);
    return !(row_mask[row] & bit) && !(col_mask[col] & bit);
}

/**
 * @brief Places a number and updates constraint tracking
 * @param n Size of the Latin Square
 * @param row Row position
 * @param col Column position
 * @param num Number to place
 * @param square 2D array representing the puzzle
 */
void place_number(int n, int row, int col, int num, short square[n][n]) {
    square[row][col] = num;
    int bit = 1 << (num - 1);
    row_mask[row] |= bit;
    col_mask[col] |= bit;
}

/**
 * @brief Removes a number and updates constraint tracking
 * @param n Size of the Latin Square
 * @param row Row position
 * @param col Column position
 * @param num Number to remove
 * @param square 2D array representing the puzzle
 */
void remove_number(int n, int row, int col, int num, short square[n][n]) {
    square[row][col] = 0;
    int bit = 1 << (num - 1);
    row_mask[row] &= ~bit;
    col_mask[col] &= ~bit;
}
