// Copyright 2022 Novozhilov Alexander
#include <omp.h>
#include <gtest/gtest.h>
#include <vector>
#include "./matrix_mult.h"

TEST(Matrix_Multiplication_TBB, get_works) {
    SparseMatrix matrix(3, 3);
    EXPECT_NO_THROW(matrix.get(1, 1));
}

TEST(Matrix_Multiplication_TBB, get_throws_exception) {
    SparseMatrix matrix(3, 3);
    EXPECT_ANY_THROW(matrix.get(4, 4));
}

TEST(Matrix_Multiplication_TBB, multiplication_works) {
    SparseMatrix matrix1(3, 5);
    SparseMatrix matrix2(5, 6);
    EXPECT_NO_THROW(matrix1.multiply_seq(matrix2));
}

TEST(Matrix_Multiplication_TBB, multiplication_throws_exception) {
    SparseMatrix matrix1(3, 6);
    SparseMatrix matrix2(5, 6);
    EXPECT_ANY_THROW(matrix1.multiply_seq(matrix2));
}

TEST(Matrix_Multiplication_TBB, result_matrix_has_correct_size) {
    SparseMatrix matrix1(3, 6);
    SparseMatrix matrix2(6, 10);
    SparseMatrix result = matrix1.multiply_seq(matrix2);
    EXPECT_EQ(result.getM(), matrix1.getM());
    EXPECT_EQ(result.getN(), matrix2.getN());
}

TEST(Matrix_Multiplication_TBB, parallel_multiplication_returns_same_result) {
    SparseMatrix matrix1(3, 6);
    SparseMatrix matrix2(6, 3);
    SparseMatrix result1 = matrix1.multiply_parallel(matrix2);
    SparseMatrix result2 = matrix1.multiply_seq(matrix2);
    ASSERT_TRUE(result1 == result2);
}

// TEST(Matrix_Multiplication_TBB, parallel_multiplication_works) {
//  SparseMatrix matrix1(100, 100);
//  SparseMatrix matrix2(100, 100);
//  double startSeq = omp_get_wtime();
//  SparseMatrix result1 = matrix1.multiply_seq(matrix2);
//  double finishSeq = omp_get_wtime();
//  double startParallel = omp_get_wtime();
//  SparseMatrix result2 = matrix1.multiply_parallel(matrix2);
//  double finishParallel = omp_get_wtime();
//  std::cout << "Sequential time: " << finishSeq - startSeq<< " s." << std::endl;
//  std::cout << "Parallel time: " << finishParallel - startParallel << " s." << std::endl;
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
