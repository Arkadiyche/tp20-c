#include <iostream>
#include "gtest/gtest.h"

extern "C" {
     #include "matrix.h"
     #include "matrix.h"
}

TEST(freeMatrix1, emptyMatrix) {
	Matrix matrix1;
	matrix1.n = 3;
	matrix1.m = 3;
	matrix1.mat = NULL;
	ASSERT_EQ(freeMatrix(matrix1), 1);
}

TEST(freeMatrix2, emptyMatrix) {
	Matrix matrix2;
	matrix2.n = 0;
	matrix2.m = 0;
	ASSERT_EQ(freeMatrix(matrix2), 1);
}
