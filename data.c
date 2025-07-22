/**
 * @file data.c
 * @brief Implementation of data input/output operations
 * 
 * Handles reading Latin Square puzzles from input files and
 * writing solved puzzles to output files.
 */

#include "data.h"
#include "checks.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Writes a completed Latin Square to an output file
 * @param n Size of the Latin Square (n x n)
 * @param square 2D array containing the solved Latin Square
 * @param outFileName Name of the output file to create
 * 
 * The output format is:
 * First line: size n
 * Following n lines: n numbers each (the solved square)
 */
void writeLatinSquare(short n, short square[n][n], char *outFileName) {
    printf("Saving to %s...\n", outFileName);
    FILE *file = fopen(outFileName, "w");
    if (file == NULL) {
        printf("Error: Could not open output file for writing.\n");
        return; 
    }
    fprintf(file, "%hd\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%hd ", abs(square[i][j]));
        }
        fprintf(file, "\n");
    }
    printf("Saved successfully!\n");
    fclose(file);
}

/**
 * @brief Reads a Latin Square puzzle from an input file
 * @param file File pointer to read from (must be already opened)
 * @param n Size of the Latin Square to read
 * @param square 2D array to store the puzzle (0 = empty cell)
 * @return 0 on successful read, 1 on error
 * 
 * Expected input format:
 * - Numbers from 0 to n (0 represents empty cells)
 * - Exactly n*n numbers after the size
 * - No extra data after the puzzle
 */
int readLatinSquare(FILE *file, short n, short square[n][n]) {
    short num;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(file, "%hd", &num) != 1) {
                printf("Error: Malformed data or not enough numbers in the input file.\n");
                fclose(file);
                return 1;
            }
            if (num < 0 || num > n) {
                printf("Error: Invalid number %hd found in the input file.\n", num);
                fclose(file);
                return 1;
            }
            square[i][j] = num;
        }
    }

    if (fscanf(file, "%hd", &num) == 1) {
        printf("Error: Extra data found at the end of the input file.\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}
