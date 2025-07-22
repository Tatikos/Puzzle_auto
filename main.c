#include "data.h"
#include "checks.h"
#include "autoplay.h"
#define MAX_N 9

int getUserConfirmation() {
    char response;
    printf("Are you ready to solve this puzzle? (y/n): ");
    scanf(" %c", &response);
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
    strcpy(outFileName, "out-");
    strcat(outFileName, filename);

    short n;
    fscanf(file, "%hd", &n);
    if (n < 1 || n > MAX_N) {
        printf("Invalid size\n");
        return 1;
    }

    short square[n][n];
    if (readLatinSquare(file, n, square) != 0) {
        return 1;
    }
    displayLatinSquare(n, square);
    
    if (!getUserConfirmation()) {
        printf("Puzzle solving cancelled.\n");
        free(outFileName);
        return 0;
    }
    
    initialize(n, square);
    bool solved = solve_latin_square(n, square);
    
    if (solved) {
        printf("Puzzle solved successfully!\n");
        displayLatinSquare(n, square);
        writeLatinSquare(n, square, outFileName);
    } else {
        printf("This Latin square is not solvable!\n");
        free(outFileName);
    }

    return 0;
}