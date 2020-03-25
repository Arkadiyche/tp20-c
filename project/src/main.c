#include "matrix.h"
#include "nn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE* a;
    Matrix input;
    FILE* b;
    FILE* output;
    a = fopen(argv[2], "r");
    b = fopen(argv[1], "r");
    output = fopen(argv[3], "w");
    /*if (f == NULL || b == NULL) {
        return 1;
    }*/
    Layer *A = readArchitectures(a);
    input = readMatrix(b);
    for (int i = 0; i < sizeof(*A)/sizeof(A); i++) {
        if (strcmp(A[i].name, "Dense") == 0) {
            input = Dense(input, A[i]);
        } else if (strcmp(A[i].name, "ReLU") == 0) {
            input = ReLU(input);
        }
        free(A[i].fname);    }
    fprintMatrix(input, output);
    freeMatrix(input);
    free(A);
    fclose(a);
    fclose(b);
    fclose(output);
    return 0;
}
