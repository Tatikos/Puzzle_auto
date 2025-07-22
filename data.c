#include "data.h"
#include "checks.h"

void writeLatinSquare(short n, short square[n][n], char *outFileName) {
    printf("Saving to %s...\n", outFileName);
    FILE *file = fopen(outFileName, "w");
    if (file == NULL) {
        printf("Error opening file");
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
    exit(0);
}

int readLatinSquare(FILE *file, short n, short square[n][n]) {
    short num;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(file, "%hd", &num) != 1) {
                printf("Error reading data or less data\n");
                return 1;
            }
            if (num > n) {
                printf("Invalid number\n");
                return 1;
            }
            square[i][j] = num;
        }
    }

    if (fscanf(file, "%hd", &num) == 1) {
        printf("Extra data\n");
        return 1;
    }

    fclose(file);
    return 0;
}