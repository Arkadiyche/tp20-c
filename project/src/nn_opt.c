#include "nn_opt.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

Matrix Dense(Matrix input, Layer A) {
    pthread_t thread;
    FILE* mat;
    FILE* vec;
    char str[255];
    sprintf(str, "%s/%s", A.fname, "matrix.txt");
    mat = fopen(str, "r");
    sprintf(str, "%s/%s", A.fname, "vector.txt");
    vec = fopen(str, "r");
    double* vector;
    MF* mf;
    mf->f = mat;
    pthread_create(&thread, NULL, readMatrix, (void*) &mf);
    vector = readVector(vec);
    pthread_join(thread, NULL);
    mf->matrix = multiply(input, mf->matrix);
    for (int i = 0; i < (mf->matrix).n; i++) {
        for (int j = 0; j < (mf->matrix).m; j++) {
            (mf->matrix).mat[i][j] += vector[i];
        }
    }
    free(vector);
    fclose(mat);
    fclose(vec);
    freeMatrix(input);
    return mf->matrix;
}

Matrix ReLU(Matrix matrix) {
    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.m; j++) {
            if (matrix.mat[i][j] < 0) {
                matrix.mat[i][j] = 0;
            }
        }
    }
    return matrix;
}

Layer readArchitecture(FILE *f) {
    char c = getc(f);
    Layer A;
    char *s;
    long pos = ftell(f);
    size_t len = 0;
    if (c == 'D') {
        A.name = "Dense";
        pos += 6;
        fseek(f, pos, SEEK_SET);
    } else if (c == 'R') {
        A.name = "ReLU";
        A.input_dim = 0;
        A.output_dim = 0;
        pos += 5;
        fseek(f, pos, SEEK_SET);
    }
    while ((c = getc(f)) != '"' && c != EOF && c != '\n') {
        len++;
    }
    s = malloc((len)*sizeof(char));
    fseek(f, pos, SEEK_SET);
    fread(s, 1, len, f);
    A.fname = s;
    if (strcmp(A.name, "Dense") == 0) {
        fscanf(f, "\",%d,%d", &A.input_dim, &A.output_dim);
    }
    while ((c = getc(f)) != '\n' && c != EOF) {/*printf("%c", c);*/}
    return A;
}

Layer* readArchitectures(FILE *f) {
    char c;
    int n = 0;
    while ((c=getc(f)) != EOF) {
        if (c == '\n') {
            n++;
        }
    }
    rewind(f);
    Layer* A = malloc(n * sizeof(Layer));
    for (int i = 0; i < n; i++) {
        A[i] = readArchitecture(f);
    }
    return A;
}
