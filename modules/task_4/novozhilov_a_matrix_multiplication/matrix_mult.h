// Copyright 2022 Novozhilov Alexander
#ifndef MODULES_TASK_4_NOVOZHILOV_A_MATRIX_MULTIPLICATION_MATRIX_MULT_H_
#define MODULES_TASK_4_NOVOZHILOV_A_MATRIX_MULTIPLICATION_MATRIX_MULT_H_

#include <vector>
#include <string>
#include <stdexcept>
#include <complex>
#include "../../../3rdparty/unapproved/unapproved.h"

class SparseMatrix {
 private:
    int m;
    int n;
    std::vector<std::complex<int>> values;
    std::vector<int> columnIndexes;
    std::vector<int> rowCounter;
 public:
    SparseMatrix(int m, int n);
    explicit SparseMatrix(std::vector<std::vector<std::complex<int>>> matrix);
    SparseMatrix multiply_seq(const SparseMatrix& matrix)const;
    SparseMatrix multiply_parallel(const SparseMatrix& matrix)const;
    int getM()const;
    int getN()const;
    std::complex<int> get(int row, int col)const;
    void print();
    bool operator==(const SparseMatrix& matrix)const;
 private:
    std::vector<std::vector<std::complex<int>>> getRandomMatrix(int m, int n);
    void printFullMatrix(std::vector<std::vector<std::complex<int>>>)const;
    std::vector<std::vector<std::complex<int>>> getFullMatrix();
    std::vector<std::vector<std::complex<int>>> getEmptyMatrix(int m, int n) const;
};


#endif  // MODULES_TASK_4_NOVOZHILOV_A_MATRIX_MULTIPLICATION_MATRIX_MULT_H_
