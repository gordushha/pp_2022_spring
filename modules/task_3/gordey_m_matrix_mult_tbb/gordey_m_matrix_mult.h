// Copyright 2018 Nesterov Alexander
#ifndef MODULES_TASK_3_GORDEY_M_MATRIX_MULT_TBB_GORDEY_M_MATRIX_MULT_H_
#define MODULES_TASK_3_GORDEY_M_MATRIX_MULT_TBB_GORDEY_M_MATRIX_MULT_H_
#include <tbb/tbb.h>
#include <vector>
#include <string>
class SparseM {
 public:
     int rows, cols;
      std::vector<int> col_idx;
      std::vector<int> row;
      std::vector<double> value;
      SparseM() :rows(0), cols(0) {}
      SparseM(double* arr, int rows, int cols) :rows(rows), cols(cols) {
           int k = 0;
           bool flag = true;
           for (int i = 0; i < cols; i++) {
                 for (int j = 0; j < rows; j++) {
                      if (arr[j*rows + i] != 0) {
                            if (flag) {
                                 col_idx.push_back(k);
                                 flag = false;
                            }
                            value.push_back(arr[j*rows + i]);
                            row.push_back(j);
                            k++;
                      }
                 }
                 if (flag)  col_idx.push_back(k);
                 flag = true;
           }
           col_idx.push_back(k);
      }
      SparseM(const SparseM& lhs) : rows(lhs.rows),
           cols(lhs.cols), col_idx(lhs.col_idx),
           row(lhs.row), value(lhs.value) {}
      SparseM& operator = (const SparseM& lhs) {
           if (this == &lhs) return (*this);
           rows = lhs.rows;
           cols = lhs.cols;
           col_idx = lhs.col_idx;
           row = lhs.row;
           value = lhs.value;
           return (*this);
      }
      friend SparseM operator *(const SparseM& A, const SparseM& B);
      friend bool operator == (const SparseM& A, const SparseM& B) {
           if (A.col_idx == B.col_idx &&
           A.rows == B.rows && A.value == B.value &&
                 A.cols == B.cols && A.row == B.row) return true;
           return false;
     }
};
void transport(SparseM* ptr);
SparseM Mult_parallel(const SparseM& A, const SparseM& B);
double* create_random_matrix(int size_n);
#endif  // MODULES_TASK_3_GORDEY_M_MATRIX_MULT_TBB_GORDEY_M_MATRIX_MULT_H_
