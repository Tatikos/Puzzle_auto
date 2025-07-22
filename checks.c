#include "checks.h"
#include "autoplay.h"
#include <limits.h>
#include <string.h>

int row_mask[9] = {0};
int col_mask[9] = {0};

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

int containsChar(const char *str, char ch) {
    while (*str != '\0') {
        if (*str == ch) {
            return 1;
        }
        str++;
    }
    return 0;
}

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

bool is_safe(int n, int row, int col, int num) {
    int bit = 1 << (num - 1);
    return !(row_mask[row] & bit) && !(col_mask[col] & bit);
}

void place_number(int n, int row, int col, int num, short square[n][n]) {
    square[row][col] = num;
    int bit = 1 << (num - 1);
    row_mask[row] |= bit;
    col_mask[col] |= bit;
}

void remove_number(int n, int row, int col, int num, short square[n][n]) {
    square[row][col] = 0;
    int bit = 1 << (num - 1);
    row_mask[row] &= ~bit;
    col_mask[col] &= ~bit;
}
