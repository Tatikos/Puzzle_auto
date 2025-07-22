/**
 * @file autoplay.h
 * @brief Header file for the automatic solving functionality
 * 
 * Contains function declarations for displaying puzzles and
 * the main backtracking solver algorithm.
 */

#ifndef AUTOPLAY_H
#define AUTOPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Displays a Latin Square in a formatted grid layout
 * @param n Size of the Latin Square
 * @param square 2D array representing the puzzle state
 * 
 * Shows the current state with borders and proper spacing.
 * Negative numbers are displayed in parentheses.
 */
void displayLatinSquare(short n, short square[n][n]);

/**
 * @brief Solves a Latin Square using backtracking with constraint propagation
 * @param n Size of the Latin Square
 * @param square 2D array representing the puzzle to solve
 * @return true if puzzle was solved successfully, false if unsolvable
 * 
 * Uses recursive backtracking with the Most Constrained Variable heuristic
 * for efficient solving. Displays each step of the solving process.
 */
bool solve_latin_square(int n, short square[n][n]);

#endif