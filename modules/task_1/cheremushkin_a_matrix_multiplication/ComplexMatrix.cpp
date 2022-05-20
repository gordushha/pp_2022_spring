// Copyright 2022 Cheremushkin Kirill
#include "../../../modules/task_1/cheremushkin_a_matrix_multiplication/ComplexMatrix.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <complex>
#include <iostream>
#include <random>
#include <cstring>
MatrixComplex::MatrixComplex() : Size{ 3 }, NonZero{ 3 },
values{ {3, 2}, {4, 3}, {2, 4} }, rows { 0, 1, 2 },
columnIndexes { 0, 1, 2, 2 } {
}
MatrixComplex::MatrixComplex(const MatrixComplex &tmp) : Size{ tmp.Size },
NonZero{ tmp.NonZero },
values{ tmp.values }, rows{ tmp.rows },
columnIndexes{ tmp.columnIndexes } {
}
MatrixComplex::MatrixComplex(int size) {
    std::vector<std::vector<std::complex<int>>> matrix = getRandomMatrix(size);
    Size = static_cast<int>(matrix.size());
    NonZero = 0;
    std::complex<int> zero(0, 0);
    this->columnIndexes.push_back(0);
    int counter = 0;
    for (size_t i = 0; i < static_cast<size_t>(matrix.size()); i++) {
        for (size_t j = 0; j < static_cast<size_t>(matrix[i].size()); j++) {
            if (matrix[i][j] != zero) {
                values.push_back(matrix[i][j]);
                rows.push_back(static_cast<int>(j));
                NonZero++;
                counter++;
            }
        }
        columnIndexes.push_back(counter);
    }
}
MatrixComplex::MatrixComplex(
    std::vector<std::vector<std::complex<int>>> matrix) {
    Size = static_cast<int>(matrix.size());
    NonZero = 0;
    std::complex<int> zero(0, 0);
    this->columnIndexes.push_back(0);
    int counter = 0;
    for (size_t i = 0; i < static_cast<size_t>(matrix.size()); i++) {
        for (size_t j = 0; j < static_cast<size_t>(matrix[i].size()); j++) {
            if (matrix[i][j] != zero) {
                values.push_back(matrix[i][j]);
                rows.push_back(static_cast<int>(j));
                NonZero++;
                counter++;
            }
        }
        columnIndexes.push_back(counter);
    }
}
MatrixComplex& MatrixComplex::operator=(const MatrixComplex& tmp) {
    Size = tmp.Size;
    NonZero = tmp.NonZero;
    values = tmp.values;
    rows = tmp.rows;
    columnIndexes = tmp.columnIndexes;
    return *this;
}
std::complex<int> MatrixComplex::get(int row, int col) const {
    if (row > Size || col > Size || row < 0 || col < 0) {
        throw std::invalid_argument("index out of matrix range");
    }

    int currRow;
    for (int pos = columnIndexes[col];
        pos < columnIndexes[static_cast<size_t>(col) + 1]; pos++) {
        currRow = rows[pos];
        if (currRow == row) {
            return values[pos];
        }
    }
    return std::complex<int>();
}

int MatrixComplex::getSize() {
    return Size;
}

int MatrixComplex::getNonZero() {
    return NonZero;
}

void MatrixComplex::setSize(int s) {
    if (s < 0) {
        throw std::invalid_argument("value < 0");
    }
     Size = s;
}

void MatrixComplex::setNonZero(int n) {
    if (n < 0) {
        throw std::invalid_argument("value < 0");
    }
    NonZero = n;
}

std::vector<std::complex<int>> MatrixComplex::getValues() {
     return values;
}

std::vector<int> MatrixComplex::getRows() {
     return rows;
}

std::vector<int> MatrixComplex::getColumnIndex() {
     return columnIndexes;
}
std::vector<std::vector<std::complex<int>>>
MatrixComplex::getRandomMatrix(int size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<std::vector<std::complex<int>>> result;
    for (int i = 0; i < size; i++) {
        std::vector<std::complex<int>> vec;
        for (int j = 0; j < size; j++) {
            if (gen() % 100 <= 30) {
                std::complex<int> complexNumber(gen() % 10, (gen() % 10));
                vec.push_back(complexNumber);
            } else {
                std::complex<int> complexNumber(0, 0);
                vec.push_back(complexNumber);
            }
        }
        result.push_back(vec);
    }
    return result;
}
MatrixComplex MatrixComplex::Multiply(
    MatrixComplex left, MatrixComplex right) {
    if (left.Size != right.Size) {
        throw std::invalid_argument("invalid matrix");
    }
    int size = left.Size;
    std::vector<std::complex<int>> values;
    std::vector<int> rows;
    std::vector<int> columnIndexes;
    std::vector<int> temp;
    temp.resize(size);
    int nonZero = 0;
    columnIndexes.push_back(0);
    for (int i = 0; i < size; i++) {
        for (size_t f = 0; f < temp.size(); f++) {
            temp[f] = -1;
        }
        for (int j = right.columnIndexes[i];
            j < right.columnIndexes[static_cast<size_t>(i) + 1]; j++) {
            int row = right.rows[j];
            temp[row] = j;
        }
        for (int j = 0; j < size; j++) {
            std::complex<int> sum = 0;
            for (int k = left.columnIndexes[j];
                k < left.columnIndexes[static_cast<size_t>(j) + 1]; k++) {
                int row = left.rows[k];
                int index = temp[row];
                if (index != -1) {
                    sum = {sum.real() + (left.values[k].real() *
                        right.values[index].real()) -
                        left.values[k].imag() * right.values[index].imag(),
                        sum.imag()+
                        (left.values[k].real() * right.values[index].imag()+
                        left.values[k].imag() * right.values[index].real())
                    };
                }
            }
            if (sum != 0) {
                rows.push_back(j);
                values.push_back(sum);
                nonZero++;
            }
        }
        columnIndexes.push_back(nonZero);
    }
    // delete[] temp;
    MatrixComplex res = MatrixComplex();
    res.Size = size;
    res.rows.resize(rows.size());
    res.values.resize(values.size());
    res.columnIndexes.resize(columnIndexes.size());
    for (int i = 0; i < nonZero; i++) {
        res.rows[i] = rows[i];
        res.values[i] = values[i];
    }
    for (size_t i = 0; i < columnIndexes.size(); i++) {
        res.columnIndexes[i] = columnIndexes[i];
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, const MatrixComplex& p) {
    os << "values";
    for (int i = 0; i < p.NonZero; i++) {
        os << "[" << i << "]" << p.values[i] << ",";
    }
    os << std::endl;
    os << "Rows:";
    for (size_t i = 0; i < p.rows.size(); i++) {
        os << "[" << i << "] " << p.rows[i] << ", ";
    }
    os << std::endl;
    os << "ColumnIndx: ";
    for (size_t i = 0; i < p.columnIndexes.size(); i++) {
        os << "[" << i << "] " << p.columnIndexes[i] << ", ";
    }
    os << std::endl;
    return os;
}

std::istream& operator>>(std::istream& in, MatrixComplex& p) {
    std::cout << "VVedite razmernost: ";
    in >> p.Size;
    std::cout << "Vvedite kol-vo NonZero elements: ";
    in >> p.NonZero;
    p.values = {};
    p.values.resize(p.NonZero);
    std::vector<std::complex<int>> bufV;
    std::vector<int> bufR;
    std::vector<int> bufC;
    int flag = p.NonZero;
    bool flagc = false;
    bool flagIns = false;
    std::complex<int> buf;
    int b1;
    int b2;
    std::cout << "Column: " << "I" << std::endl;
    std::cout << "Rows : " << "J" << std::endl;
    for (int i = 0; i < p.Size; i++) {
        for (int j = 0; j < p.Size; j++) {
            if (flag > 0) {
                std::cout << "Input elements " << "[" << i
                    << "]" << "[" << j << "]" << ":" << std::endl;
                std::cout << "Input  real: ";
                in >> b1;
                if (b1 == 0) {
                    continue;
                }
                std::cout << "Input image: ";
                in >> b2;
                std::cout << std::endl;
                buf = { b1, b2 };
                if (buf.real() != 0 && buf.imag() != 0) {
                    flagIns = true;
                    bufV.push_back(buf);
                    bufR.push_back(j);
                    flag--;
                    if (flagc == false) {
                        bufC.push_back(static_cast<int>(bufV.size()) - 1);
                        flagc = true;
                    }
                    if (i == p.Size - 1 && j == p.Size - 1) {
                        bufC.push_back(static_cast<int>(bufV.size()) - 1);
                    }
                }
            } else {
               break;
            }
        }
        flagc = false;
        if (flagIns == false) {
            bufC.push_back(-2);
        }
        flagIns = false;
    }
    for (int i = 0; i < p.NonZero; i++) {
         p.values[i] = bufV[i];
    }
    p.rows = {};
    p.rows.resize(bufR.size());
    for (size_t i = 0; i < bufR.size(); i++) {
         p.rows[i] = bufR[i];
    }
    p.columnIndexes = {};
    p.columnIndexes.resize(bufC.size());
    for (size_t i = 0; i < bufC.size(); i++) {
         p.columnIndexes[i] = bufC[i];
    }
    return in;
}
