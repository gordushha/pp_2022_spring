// Copyright 2022 Uglinskii Bogdan
#include <gtest/gtest.h>
#include <omp.h>

#include <iostream>
#include <vector>

#include "./crs_multiplication.h"

TEST(Multiplication_seq, crs_50x50_30) {
  MatrixCRS matrix_A = GenerateRandomMatrixCRS(50, 50, 30);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(50, 50, 30);

  MatrixCRS matrix_C;
  CRSMultiply(matrix_A, matrix_B, &matrix_C);

  std::vector<std::vector<double>> C;

  NormalMulty(ExpandMatrix(matrix_A), ExpandMatrix(matrix_B), &C);
  MatrixCRS crs_C;
  ConvertToCRS(C, &crs_C);
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, crs_C));
}

TEST(Multiplication_parallel, 3x3_4) {
  double t1, t2, t1_, t2_;

  MatrixCRS matrix_A = GenerateRandomMatrixCRS(3, 3, 4);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(3, 3, 4);

  MatrixCRS matrix_C;
  t1 = omp_get_wtime();
  CRSMultiply(matrix_A, matrix_B, &matrix_C);
  t2 = omp_get_wtime();

  MatrixCRS C_omp;
  t1_ = omp_get_wtime();
  CRSMultiplyOMP(matrix_A, matrix_B, &C_omp);
  t2_ = omp_get_wtime();
  std::cout << "NO OMP time = " << t2 - t1 << "\nOMP time = " << t2_ - t1_
            << "\nAcceleration = " << (t2 - t1) / (t2_ - t1_) << "\n";
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, C_omp));
}

TEST(Multiplication_parallel, 50x50_30) {
  double t1, t2, t1_, t2_;

  MatrixCRS matrix_A = GenerateRandomMatrixCRS(50, 50, 30);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(50, 50, 30);

  MatrixCRS matrix_C;
  t1 = omp_get_wtime();
  CRSMultiply(matrix_A, matrix_B, &matrix_C);
  t2 = omp_get_wtime();

  MatrixCRS C_omp;
  t1_ = omp_get_wtime();
  CRSMultiplyOMP(matrix_A, matrix_B, &C_omp);
  t2_ = omp_get_wtime();
  std::cout << "NO OMP time = " << t2 - t1 << "\nOMP time = " << t2_ - t1_
            << "\nAcceleration = " << (t2 - t1) / (t2_ - t1_) << "\n";
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, C_omp));
}

TEST(Multiplication_parallel, 200x200_350) {
  double t1, t2, t1_, t2_;

  MatrixCRS matrix_A = GenerateRandomMatrixCRS(200, 200, 350);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(200, 200, 350);

  MatrixCRS matrix_C;
  t1 = omp_get_wtime();
  CRSMultiply(matrix_A, matrix_B, &matrix_C);
  t2 = omp_get_wtime();

  MatrixCRS C_omp;
  t1_ = omp_get_wtime();
  CRSMultiplyOMP(matrix_A, matrix_B, &C_omp);
  t2_ = omp_get_wtime();
  std::cout << "NO OMP time = " << t2 - t1 << "\nOMP time = " << t2_ - t1_
            << "\nAcceleration = " << (t2 - t1) / (t2_ - t1_) << "\n";
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, C_omp));
}

TEST(Multiplication_parallel, 250x250_400) {
  double t1, t2, t1_, t2_;

  MatrixCRS matrix_A = GenerateRandomMatrixCRS(250, 250, 400);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(250, 250, 400);

  MatrixCRS matrix_C;
  t1 = omp_get_wtime();
  CRSMultiply(matrix_A, matrix_B, &matrix_C);
  t2 = omp_get_wtime();

  MatrixCRS C_omp;
  t1_ = omp_get_wtime();
  CRSMultiplyOMP(matrix_A, matrix_B, &C_omp);
  t2_ = omp_get_wtime();
  std::cout << "NO OMP time = " << t2 - t1 << "\nOMP time = " << t2_ - t1_
            << "\nAcceleration = " << (t2 - t1) / (t2_ - t1_) << "\n";
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, C_omp));
}

TEST(Multiplication_parallel, 300x300_1000) {
  double t1, t2, t1_, t2_;

  MatrixCRS matrix_A = GenerateRandomMatrixCRS(300, 300, 1000);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(300, 300, 1000);

  MatrixCRS matrix_C;
  t1 = omp_get_wtime();
  CRSMultiply(matrix_A, matrix_B, &matrix_C);
  t2 = omp_get_wtime();

  MatrixCRS C_omp;
  t1_ = omp_get_wtime();
  CRSMultiplyOMP(matrix_A, matrix_B, &C_omp);
  t2_ = omp_get_wtime();
  std::cout << "NO OMP time = " << t2 - t1 << "\nOMP time = " << t2_ - t1_
            << "\nAcceleration = " << (t2 - t1) / (t2_ - t1_) << "\n";
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, C_omp));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
