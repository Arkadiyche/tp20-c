#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Matrix readMatrix(FILE *f) {
    int n = 0;
    int m = 0;
    int k = 0;
    int kluch = 0;
    char c;
    Matrix matrix;
    while ((c = getc(f)) != EOF) {
        if (c != ' ' && c != '\n' && c != '-' && kluch != 1) {
            m++;
            kluch = 1;
        } else {
            kluch = 0;
        }
        if (c == '\n') {
            n++;
            if (k != 0 && m != k && m != 0) {
                printf("Error matrix\n");
            }
            if (m != 0) {
                k = m;
            }
            m = 0;
        }
    }
    rewind(f);
    matrix.n = n;
    matrix.m = k;
    matrix.mat = malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix.mat[i] = malloc(k * sizeof(double));
        for (int j = 0; j < k; j++) {
            fscanf(f, "%lf", &matrix.mat[i][j]);
        }
    }
    return matrix;
}
int freeMatrix(Matrix matrix) {
    if (matrix.n == 0 || matrix.m == 0 || matrix.mat == NULL){
        return 1;
    }
    for (int i = 0; i < matrix.n; i++) {
        free(matrix.mat[i]);
    }
    free(matrix.mat);
    return 0;
}

double* readVector(FILE *f) {
    double* vector;
    char c;
    int kluch = 0;
    int n = 0;
    while ((c = getc(f)) != EOF) {
        if (c != ' ' && c != '\n' && c != '-' && kluch != 1) {
            n++;
            kluch = 1;
        } else {
            kluch = 0;
        }
    }
    rewind(f);
    vector = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        fscanf(f, "%lf", &vector[i]);
    }
    return vector;
}

Matrix multiply(Matrix one, Matrix two) {
    Matrix res;
    res.n = one.n;
    res.m = two.m;
    res.mat = malloc(res.n * sizeof(double*));
    for (int i = 0; i < res.n; i++) {
        res.mat[i] = malloc(res.m * sizeof(double));
        for (int j = 0; j < res.m; j++) {
            res.mat[i][j] = 0;
            for (int k =0; k < res.n; k++) {
                res.mat[i][j] += one.mat[i][k]*two.mat[k][j];
            }
        }
    }
    freeMatrix(two);
    return res;
}

void printMatrix(Matrix matrix) {
    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.m; j++) {
                printf("%lf ", matrix.mat[i][j]);
        }
        printf("\n");
    }
}
void fprintMatrix(Matrix matrix, FILE* f) {
    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.m; j++) {
                fprintf(f, "%lf ", matrix.mat[i][j]);
        }
        fprintf(f, "\n");
    }
}
