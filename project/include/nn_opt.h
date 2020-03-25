#ifndef HW2FINALLY_PROJECT_INCLUDE_NN_OPT_H_
#define HW2FINALLY_PROJECT_INCLUDE_NN_OPT_H_

#include <stdio.h>
#include <matrix_opt.h>

struct Layer {
    int input_dim;
    int output_dim;
    char* fname;
    char* name;
};

typedef struct Layer Layer;

Layer readArchitecture(FILE*);
Layer* readArchitectures(FILE*);
Matrix Dense(Matrix, Layer);
Matrix ReLU(Matrix);


#endif  // HW2FINALLY_PROJECT_INCLUDE_NN_OPT_H_
