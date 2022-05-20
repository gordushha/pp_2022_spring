// Copyright 2022 Cheremushkin Kirill
#pragma once
#ifndef MODULES_TASK_1_CHEREMUSHKIN_K_MATRIX_MULTIPLICATION_MATRIX_MULT_H_
#define MODULES_TASK_1_CHEREMUSHKIN_K_MATRIX_MULTIPLICATION_MATRIX_MULT_H_
#include <vector>
#include <string>
#include <stdexcept>
#include <complex>
#include <iostream>
#include <random>
#include <cstring>
class MatrixComplex {
 private:
    int Size;  // Kol-vo strok i stolbcov
    int NonZero;  // Kol-vo ne nulevih
    std::vector<std::complex<int>> values;  // Vector znacheniy
    std::vector<int> rows;  // Vector numeric rows
    std::vector<int> columnIndexes;  // Vector indexov

 public:
    MatrixComplex();
    MatrixComplex(const MatrixComplex& tmp);
    explicit MatrixComplex(int size);
    explicit MatrixComplex(std::vector<std::vector<std::complex<int>>> matrix);
    MatrixComplex& operator=(const MatrixComplex& tmp);
    std::complex<int> get(int row, int col)const;
    int getSize();
    int getNonZero();
    void setSize(int s);
    void setNonZero(int n);
    std::vector<std::complex<int>> getValues();
    std::vector<int>getRows();
    std::vector<int> getColumnIndex();
    std::vector<std::vector<std::complex<int>>> getRandomMatrix(int size);
    MatrixComplex Multiply(MatrixComplex left,
        MatrixComplex right);
    friend std::ostream& operator << (std::ostream& os, const MatrixComplex& p);
    friend std::istream& operator >> (std::istream& in, MatrixComplex& p);
};
#endif  // MODULES_TASK_1_CHEREMUSHKIN_K_MATRIX_MULTIPLICATION_MATRIX_MULT_H_
