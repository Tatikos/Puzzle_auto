#include "checks.h"
#include "autoplay.h"
#include <limits.h>
int row_mask[9] = {0}; 
int col_mask[9] = {0};  

void initialize(short n, short square[n][n]) {
    for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
        if (square[r][c] != 0) {
            int num = abs(square[r][c]);  
            row_mask[r] |= (1 << (num - 1));  
            col_mask[c] |= (1 << (num - 1));  
            }
        }
    }
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
    bool found = false;

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (square[r][c] == 0) {
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
                    found = true;
                }
                if (min_options == 1) return true;
            }
        }
    }
    return found;
}
bool is_safe(int n, int row, int col, int num) {
    int bit = 1 << (num - 1);
    return !(row_mask[row] & bit) && !(col_mask[col] & bit);
}

void place_number(int n, int row, int col, int num, short square[n][n]) {
    square[row][col] = num;
    row_mask[row] |= (1 << (num - 1));
    col_mask[col] |= (1 << (num - 1)); 
}
void remove_number(int n, int row, int col, int num, short square[n][n]) {
    square[row][col] = 0;
    row_mask[row] &= ~(1 << (num - 1));
    col_mask[col] &= ~(1 << (num - 1)); 
}