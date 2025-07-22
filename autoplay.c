#include "autoplay.h"
#include "checks.h"
#include "data.h"
#include <limits.h>
int k = 0;
int popnum = 0;
int pushnum = 0;
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