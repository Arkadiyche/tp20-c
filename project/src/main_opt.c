#include "matrix_opt.h"
#include "nn_opt.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    pthread_t thread;
    FILE* a;
    FILE* b;
    FILE* output;
    a = fopen(argv[2], "r");
    b = fopen(argv[1], "r");
    output = fopen(argv[3], "w");
    if (a == NULL || b == NULL || output == NULL) {
        return 1;
    }
    MF mf;
    mf.f = b;
    pthread_create(&thread, NULL, readMatrix, (void*) &mf);
    Layer *A = readArchitectures(a);
    pthread_join(thread, NULL);
    printMatrix(mf.matrix);
    for (int i = 0; i < sizeof(*A)/sizeof(A); i++) {
        if (strcmp(A[i].name, "Dense") == 0) {
            mf.matrix = Dense(mf.matrix, A[i]);
        } else if (strcmp(A[i].name, "ReLU") == 0) {
            mf.matrix = ReLU(mf.matrix);
        }
        free(A[i].fname);
    }
    fprintMatrix(mf.matrix, output);
    freeMatrix(mf.matrix);
    free(A);
    fclose(a);
    fclose(b);
    fclose(output);
    return 0;
}
