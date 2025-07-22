#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>

void writeLatinSquare(short n, short square[n][n], char *outFileName);
int readLatinSquare(FILE *file, short n, short square[n][n]);

#endif // DATA_H