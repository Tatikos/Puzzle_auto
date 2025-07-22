/**
 * @file data.h
 * @brief Header file for data input/output operations
 * 
 * Contains function declarations for reading and writing Latin Square data
 * from/to files.
 */

#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Writes a Latin Square to an output file
 * @param n Size of the Latin Square (n x n)
 * @param square 2D array representing the Latin Square
 * @param outFileName Name of the output file to write to
 */
void writeLatinSquare(short n, short square[n][n], char *outFileName);

/**
 * @brief Reads a Latin Square from an input file
 * @param file File pointer to read from
 * @param n Size of the Latin Square (n x n)
 * @param square 2D array to store the Latin Square
 * @return 0 on success, 1 on error
 */
int readLatinSquare(FILE *file, short n, short square[n][n]);

#endif // DATA_H