#include "data.h"
#include "checks.h"
#include "autoplay.h"
#include <stdlib.h>
#include <string.h>

#define MAX_N 9

int getUserConfirmation() {
    char response;
    printf("Are you ready to solve this puzzle? (y/n): ");
    scanf(" %c", &response);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return (response == 'y' || response == 'Y');
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <inputfile.txt>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    char *filename;
    if (containsChar(argv[1], '/')) {
        filename = strrchr(argv[1], '/') + 1;
    } else {
        filename = argv[1];
    }

    char *outFileName = malloc(strlen(filename) + 6);
    if (outFileName == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1;
    }
    strcpy(outFileName, "out-");
    strcat(outFileName, filename);

    short n;
    if (fscanf(file, "%hd", &n) != 1) {
        printf("Error: Could not read size 'n' from file.\n");
        free(outFileName);
        fclose(file);
        return 1;
    }

    if (n < 1 || n > MAX_N) {
        printf("Invalid size 'n'=%hd. Must be between 1 and %d.\n", n, MAX_N);
        free(outFileName);
        fclose(file);
        return 1;
    }

    short (*square)[n] = malloc(sizeof(short[n][n]));
    if (square == NULL) {
        printf("Memory allocation for square failed.\n");
        free(outFileName);
        fclose(file);
        return 1;
    }

    if (readLatinSquare(file, n, square) != 0) {
        free(square);
        free(outFileName);
        return 1;
    }

    displayLatinSquare(n, square);

    if (!getUserConfirmation()) {
        printf("Puzzle solving cancelled.\n");
        free(square);
        free(outFileName);
        return 0;
    }

    if (!initialize(n, square)) {
        printf("The initial puzzle is invalid and cannot be solved.\n");
        free(square);
        free(outFileName);
        return 1;
    }

    bool solved = solve_latin_square(n, square);

    if (solved) {
        printf("Puzzle solved successfully!\n");
        displayLatinSquare(n, square);
        writeLatinSquare(n, square, outFileName);
    } else {
        printf("the square is unsolvable\n");
        free(square);
        free(outFileName);
        exit(0);
    }

    free(square);
    free(outFileName);
    return 0;
}
