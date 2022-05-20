// Copyright 2022 Uglinskii Bogdan
#include <gtest/gtest.h>
#include <omp.h>

#include <iostream>
#include <vector>

#include "./crs_multiplication.h"

TEST(Secondary_functions, Convert_Expend) {
  std::vector<std::vector<double>> A{{0, 3, 1}, {0, 0, 0}, {5, 0, 3}};
  std::vector<std::vector<double>> expected_A{{0, 3, 1}, {0, 0, 0}, {5, 0, 3}};

  MatrixCRS crs_A;
  ConvertToCRS(A, &crs_A);

  std::vector<std::vector<double>> expended_A = ExpandMatrix(crs_A);

  ASSERT_TRUE(CompareMatrixNormal(expended_A, expected_A));
}

TEST(Secondary_functions, Transpose) {
  std::vector<std::vector<double>> A{{0, 3, 1}, {0, 0, 0}, {5, 0, 3}};
  std::vector<std::vector<double>> expected_A_T{
      {0, 0, 5}, {3, 0, 0}, {1, 0, 3}};

  MatrixCRS crs_A;
  ConvertToCRS(A, &crs_A);

  MatrixCRS crs_expected_A_T;
  ConvertToCRS(expected_A_T, &crs_expected_A_T);

  MatrixCRS crs_A_T = Transpose(crs_A);

  ASSERT_TRUE(CompareMatrixCRS(crs_A_T, crs_expected_A_T));
}

TEST(Multiplication, normal_3x3) {
  std::vector<std::vector<double>> A{{2.3, 3, 1}, {22, 4, -4}, {5, 12, 3}};
  std::vector<std::vector<double>> B{{43, 5, 1}, {3, -2, 0.3}, {12.3, 4, -1}};
  std::vector<std::vector<double>> expected_C{
      {120.2, 9.5, 2.2}, {908.8, 86, 27.2}, {287.9, 13., 5.6}};

  std::vector<std::vector<double>> C;
  NormalMulty(A, B, &C);
  ASSERT_TRUE(CompareMatrixNormal(C, expected_C));
}

TEST(Multiplication, crs_3x3_4) {
  MatrixCRS matrix_A = GenerateRandomMatrixCRS(3, 3, 4);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(3, 3, 4);

  MatrixCRS matrix_C;
  CRSMultiply(matrix_A, matrix_B, &matrix_C);

  std::vector<std::vector<double>> C;

  std::vector<std::vector<double>> exp_A = ExpandMatrix(matrix_A),
                                   exp_B = ExpandMatrix(matrix_B);

  NormalMulty(exp_A, exp_B, &C);

  MatrixCRS crs_C;
  ConvertToCRS(C, &crs_C);

  ASSERT_TRUE(CompareMatrixCRS(matrix_C, crs_C));
}

TEST(Multiplication, crs_100x100_100) {
  MatrixCRS matrix_A = GenerateRandomMatrixCRS(100, 100, 100);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(100, 100, 100);

  MatrixCRS matrix_C;
  CRSMultiply(matrix_A, matrix_B, &matrix_C);

  std::vector<std::vector<double>> C;

  std::vector<std::vector<double>> exp_A = ExpandMatrix(matrix_A),
                                   exp_B = ExpandMatrix(matrix_B);

  NormalMulty(exp_A, exp_B, &C);

  MatrixCRS crs_C;
  ConvertToCRS(C, &crs_C);

  ASSERT_TRUE(CompareMatrixCRS(matrix_C, crs_C));
}

TEST(Multiplication, crs_100x100_350) {
  MatrixCRS matrix_A = GenerateRandomMatrixCRS(100, 100, 350);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(100, 100, 350);

  MatrixCRS matrix_C;
  CRSMultiply(matrix_A, matrix_B, &matrix_C);

  std::vector<std::vector<double>> C;

  std::vector<std::vector<double>> exp_A = ExpandMatrix(matrix_A),
                                   exp_B = ExpandMatrix(matrix_B);

  NormalMulty(exp_A, exp_B, &C);

  MatrixCRS crs_C;
  ConvertToCRS(C, &crs_C);

  ASSERT_TRUE(CompareMatrixCRS(matrix_C, crs_C));
}

TEST(Multiplication, crs_100x100_2000) {
  MatrixCRS matrix_A = GenerateRandomMatrixCRS(100, 100, 2000);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(100, 100, 2000);

  MatrixCRS matrix_C;
  CRSMultiply(matrix_A, matrix_B, &matrix_C);

  std::vector<std::vector<double>> C;

  std::vector<std::vector<double>> exp_A = ExpandMatrix(matrix_A),
                                   exp_B = ExpandMatrix(matrix_B);

  NormalMulty(exp_A, exp_B, &C);

  MatrixCRS crs_C;
  ConvertToCRS(C, &crs_C);

  ASSERT_TRUE(CompareMatrixCRS(matrix_C, crs_C));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
