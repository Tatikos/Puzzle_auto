#ifndef CHECKS_H
#define CHECKS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool find_most_constrained_cell(int n, short square[n][n], int *row, int *col);
bool is_safe(int n, int row, int col, int num);
void place_number(int n, int row, int col, int num, short square[n][n]);
void remove_number(int n, int row, int col, int num, short square[n][n]);
int containsChar(const char *str, char ch);
void initialize(short n, short square[n][n]);

#endif