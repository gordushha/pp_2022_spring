// Copyright 2022 Uglinskii Bogdan
#include "../../../modules/task_1/uglinskii_b_crs_matrix/crs_multiplication.h"

#include <iostream>
#include <random>

void InitializeMatrix(int rows, int col, int NZ, MatrixCRS *M) {
  M->N = rows;
  M->M = col;
  M->NZ = NZ;
  M->value = std::vector<double>(NZ);
  M->col = std::vector<int>(NZ);
  M->row_index = std::vector<int>(rows + 1);
}

double GenerateValue(double min, double max) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::uniform_real_distribution<double> uni(min, max);

  return uni(gen);
}
MatrixCRS GenerateRandomMatrixCRS(int N, int M, int NZ) {
  MatrixCRS result;
  InitializeMatrix(N, M, 0, &result);

  if (N * M != 0) {
    double mean_nz_in_row = static_cast<double>(NZ) / (N * M);

    double prob = 0;
    double total_elements = 0;
    result.row_index[0] = (0);

    int k = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        prob = GenerateValue(0, 1);
        if (prob <= mean_nz_in_row) {
          result.value.push_back(GenerateValue(-100, 101));
          result.col.push_back(j);
          total_elements++;
          k++;
        }
      }
      result.row_index[i + 1] = total_elements;
    }

    result.NZ = result.col.size();
  }
  return result;
}

int ConvertToCRS(std::vector<std::vector<double>> input_matrix,
                 MatrixCRS *output_matrix) {
  int N, M;
  N = input_matrix.size();
  InitializeMatrix(0, 0, 0, output_matrix);
  if (N != 0) {
    M = input_matrix[0].size();
    output_matrix->N = N;
    output_matrix->M = M;

    int elements_count = 0;

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (std::fabs(input_matrix[i][j]) > 0.000001) {
          output_matrix->value.push_back(input_matrix[i][j]);
          output_matrix->col.push_back(j);
          elements_count++;
        }
      }
      output_matrix->row_index.push_back(elements_count);
    }
    output_matrix->NZ = output_matrix->value.size();
    return 0;
  } else {
    return 1;
  }
}
std::vector<std::vector<double>> ExpandMatrix(MatrixCRS M) {
  int k = 0;
  std::vector<std::vector<double>> result =
      std::vector<std::vector<double>>(M.N);
  int elements_in_row = 0;
  for (int i = 0; i < M.N; i++) {
    elements_in_row = M.row_index[i + 1] - M.row_index[i];
    for (int j = 0; j < M.M; j++) {
      if (k < M.NZ && M.col[k] == j && elements_in_row > 0) {
        result[i].push_back(M.value[k]);
        elements_in_row--;
        k++;
      } else {
        result[i].push_back(0);
      }
    }
  }

  return result;
}

void PrintMatrixInfo(MatrixCRS M) {
  std::cout << "\n------------------------------------------------"
            << std::endl;
  std::cout << "N = " << M.N << "; M = " << M.M << "; NZ = " << M.NZ
            << std::endl;
  if (M.N * M.M != 0) {
    std::cout << "mean nz in row = " << static_cast<double>(M.NZ) / (M.N * M.M)
              << std::endl;
  }

  std::cout << "Values: ";
  int val_size = M.value.size();
  for (int i = 0; i < val_size; i++) {
    std::cout << M.value[i];
    if (i < val_size - 1) std::cout << ", ";
  }
  std::cout << ";\n";

  std::cout << "Columns: ";
  int col_size = M.col.size();
  for (int i = 0; i < col_size; i++) {
    std::cout << M.col[i];
    if (i < col_size - 1) std::cout << ", ";
  }
  std::cout << ";\n";

  std::cout << "Row Index: ";
  int row_size = M.row_index.size();
  for (int i = 0; i < row_size; i++) {
    std::cout << M.row_index[i];
    if (i < row_size - 1) std::cout << ", ";
  }

  std::cout << ";\n";
  std::cout << "------------------------------------------------\n"
            << std::endl;
}
void PrintNormalMatrix(std::vector<std::vector<double>> matrix) {
  std::cout << "===================================================="
            << std::endl;
  int N = matrix.size();
  for (int i = 0; i < N; i++) {
    int M = matrix[i].size();
    for (int j = 0; j < M; j++) {
      std::cout << matrix[i][j] << "    ";
    }
    std::cout << std::endl;
  }
  std::cout << "===================================================="
            << std::endl;
}

bool CompareMatrixCRS(MatrixCRS A, MatrixCRS B) {
  if (A.N != B.N || A.NZ != B.NZ) return false;

  double precision = 0.000001;
  for (int i = 0; i < A.NZ; i++) {
    if (std::fabs(A.value[i] - B.value[i]) > precision) return false;
  }

  for (int i = 0; i < A.NZ; i++) {
    if (A.col[i] != B.col[i]) return false;
  }

  int row_size = A.row_index.size();
  for (int i = 0; i < row_size; i++) {
    if (A.row_index[i] != B.row_index[i]) return false;
  }

  return true;
}

MatrixCRS Transpose(MatrixCRS matrix) {
  MatrixCRS MT;
  InitializeMatrix(matrix.M, matrix.N, matrix.NZ, &MT);

  for (int i = 0; i < matrix.NZ; i++) {
    MT.row_index[matrix.col[i] + 1]++;
  }

  int tmp = 0;
  double S = 0;
  for (int i = 1; i <= matrix.M; i++) {
    tmp = MT.row_index[i];
    MT.row_index[i] = S;
    S += tmp;
  }

  int col1 = 0, col2 = 0, col = 0, row_idx = 0, i_idx = 0;
  double tmp_val = 0;
  for (int i = 0; i < matrix.N; i++) {
    col1 = matrix.row_index[i];
    col2 = matrix.row_index[i + 1];
    col = i;
    for (int j = col1; j < col2; j++) {
      tmp_val = matrix.value[j];
      row_idx = matrix.col[j];
      i_idx = MT.row_index[row_idx + 1];
      MT.value[i_idx] = tmp_val;
      MT.col[i_idx] = col;
      MT.row_index[row_idx + 1]++;
    }
  }

  return MT;
}
int CRSMultiply(MatrixCRS A, MatrixCRS B, MatrixCRS *C) {
  if (A.M != B.N) {
    std::cout << "Incorrect sizes of matrix\n";
    return 1;
  }
  B = Transpose(B);
  double S = 0;
  int row_NZ = 0;

  std::vector<double> vals;
  std::vector<int> col;
  std::vector<int> row_idx{0};

  for (int i = 0; i < A.N; i++) {
    row_NZ = 0;
    for (int j = 0; j < B.N; j++) {
      S = 0;
      for (int k = A.row_index[i]; k < A.row_index[i + 1]; k++) {
        for (int l = B.row_index[j]; l < B.row_index[j + 1]; l++) {
          if (A.col[k] == B.col[l]) {
            S += A.value[k] * B.value[l];
            break;
          }
        }
      }

      if (std::fabs(S) > 0.000001) {
        col.push_back(j);
        vals.push_back(S);
        row_NZ++;
      }
    }
    row_idx.push_back(row_NZ + row_idx[i]);
  }

  InitializeMatrix(A.N, B.N, col.size(), C);

  int col_size = col.size();
  for (int i = 0; i < col_size; i++) {
    C->col[i] = col[i];
    C->value[i] = vals[i];
  }
  for (int i = 0; i <= A.N; i++) {
    C->row_index[i] = row_idx[i];
  }

  return 0;
}
int NormalMulty(std::vector<std::vector<double>> A,
                std::vector<std::vector<double>> B,
                std::vector<std::vector<double>> *C) {
  *C = std::vector<std::vector<double>>(A.size());
  int row1 = A.size(), row2 = B.size(), col1 = 0, col2 = 0;

  if (row1 != 0) {
    col1 = A[0].size(), col2 = B[0].size();
    if (col1 != row2) {
      std::cout << "Incorrect sizes of matrix\n";
      return 1;
    }
  }

  for (int i = 0; i < row1; i++) {
    (*C)[i] = std::vector<double>(col2);
    for (int j = 0; j < col2; j++) {
      (*C)[i][j] = 0;
      for (int k = 0; k < col1; k++) (*C)[i][j] += A[i][k] * B[k][j];
    }
  }
  return 0;
}

bool CompareMatrixNormal(std::vector<std::vector<double>> A,
                         std::vector<std::vector<double>> B) {
  int A_N = A.size(), B_N = B.size();

  int A_M = 0, B_M = 0;

  if (A_N != 0 && B_N != 0) {
    A_M = A[0].size(), B_M = B[0].size();
    if (A_N != B_N || A_M != B_M) {
      std::cout << "Incorrect sizes of matrix\n";
      return false;
    }
  }

  for (int i = 0; i < A_N; i++) {
    for (int j = 0; j < A_M; j++) {
      if (std::fabs(A[i][j] - B[i][j]) > 0.000001) {
        std::cout << "A != B \n";
        return false;
      }
    }
  }
  return true;
}
