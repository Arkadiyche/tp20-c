#ifndef HW2FINALLY_PROJECT_INCLUDE_MATRIX_H_
#define HW2FINALLY_PROJECT_INCLUDE_MATRIX_H_

#include <stdio.h>

struct Matrix {
    int n;
    int m;
    double** mat;
};

typedef struct Matrix Matrix;

Matrix readMatrix(FILE*);
int freeMatrix(Matrix);
double* readVector(FILE*);
Matrix multiply(Matrix, Matrix);
void printMatrix(Matrix);
void fprintMatrix(Matrix, FILE*);

#endif  // HW2FINALLY_PROJECT_INCLUDE_MATRIX_H_
