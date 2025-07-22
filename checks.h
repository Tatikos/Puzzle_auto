/**
 * @file checks.h
 * @brief Header file for constraint checking and validation functions
 * 
 * Contains function declarations for validating Latin Square constraints,
 * finding optimal cells to fill, and managing number placement.
 */

#ifndef CHECKS_H
#define CHECKS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Finds the empty cell with the fewest valid number options
 * @param n Size of the Latin Square
 * @param square 2D array representing the current state
 * @param row Pointer to store the row of the most constrained cell
 * @param col Pointer to store the column of the most constrained cell
 * @return true if an empty cell was found, false if puzzle is complete
 */
bool find_most_constrained_cell(int n, short square[n][n], int *row, int *col);

/**
 * @brief Checks if a number can be safely placed at a given position
 * @param n Size of the Latin Square
 * @param row Row position to check
 * @param col Column position to check
 * @param num Number to place (1 to n)
 * @return true if placement is valid, false if it violates constraints
 */
bool is_safe(int n, int row, int col, int num);

/**
 * @brief Places a number at the specified position and updates constraints
 * @param n Size of the Latin Square
 * @param row Row position
 * @param col Column position
 * @param num Number to place
 * @param square 2D array representing the Latin Square
 */
void place_number(int n, int row, int col, int num, short square[n][n]);

/**
 * @brief Removes a number from the specified position and updates constraints
 * @param n Size of the Latin Square
 * @param row Row position
 * @param col Column position
 * @param num Number to remove
 * @param square 2D array representing the Latin Square
 */
void remove_number(int n, int row, int col, int num, short square[n][n]);

/**
 * @brief Checks if a string contains a specific character
 * @param str String to search in
 * @param ch Character to search for
 * @return 1 if character is found, 0 otherwise
 */
int containsChar(const char *str, char ch);

/**
 * @brief Initializes constraint masks from the initial puzzle state
 * @param n Size of the Latin Square
 * @param square 2D array representing the initial puzzle
 * @return true if initialization successful, false if puzzle is invalid
 */
bool initialize(short n, short square[n][n]);

#endif
