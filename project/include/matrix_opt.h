#ifndef HW2FINALLY_PROJECT_INCLUDE_MATRIX_OPT_H_
#define HW2FINALLY_PROJECT_INCLUDE_MATRIX_OPT_H_

#include <stdio.h>

struct Matrix {
    int n;
    int m;
    double** mat;
};

typedef struct Matrix Matrix;

struct MF {
    Matrix matrix;
    FILE *f;
};

typedef struct MF MF;

void* readMatrix(void*);
void freeMatrix(Matrix);
double* readVector(FILE*);
Matrix multiply(Matrix, Matrix);
void printMatrix(Matrix);
void fprintMatrix(Matrix, FILE*);

#endif  // HW2FINALLY_PROJECT_INCLUDE_MATRIX_OPT_H_
