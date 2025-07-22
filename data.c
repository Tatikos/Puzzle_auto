#include "data.h"
#include "checks.h"
#include <stdio.h>
#include <stdlib.h>

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
