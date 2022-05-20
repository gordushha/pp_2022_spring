// Copyright 2022 Uglinskii Bogdan
#ifndef MODULES_TASK_1_UGLINSKII_B_CRS_MATRIX_CRS_MULTIPLICATION_H_
#define MODULES_TASK_1_UGLINSKII_B_CRS_MATRIX_CRS_MULTIPLICATION_H_

#include <vector>

struct MatrixCRS {
  int N;
  int M;
  int NZ;

  std::vector<double> value;
  std::vector<int> col;
  std::vector<int> row_index;
};

void InitializeMatrix(int rows, int col, int NZ, MatrixCRS *M);

double GenerateValue(double min, double max);
MatrixCRS GenerateRandomMatrixCRS(int N, int M, int NZ);

int ConvertToCRS(std::vector<std::vector<double>> input_matrix,
                 MatrixCRS *output_matrix);
std::vector<std::vector<double>> ExpandMatrix(MatrixCRS M);

void PrintMatrixInfo(MatrixCRS M);
void PrintNormalMatrix(std::vector<std::vector<double>> M);

bool CompareMatrixCRS(MatrixCRS A, MatrixCRS B);

MatrixCRS Transpose(MatrixCRS M);
int CRSMultiply(MatrixCRS A, MatrixCRS B, MatrixCRS *C);
int NormalMulty(std::vector<std::vector<double>> A,
                std::vector<std::vector<double>> B,
                std::vector<std::vector<double>> *C);

bool CompareMatrixNormal(std::vector<std::vector<double>> A,
                         std::vector<std::vector<double>> B);

#endif  // MODULES_TASK_1_UGLINSKII_B_CRS_MATRIX_CRS_MULTIPLICATION_H_
