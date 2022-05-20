// Copyright 2022 Chernyh Daria
#include <tbb/parallel_reduce.h>
#include <iostream>
#include <functional>
#include <numeric>
#include"../../../modules/task_3/chernyh_d_simpson/simpson.h"

void SimpsonCalcul::operator() (const tbb::blocked_range<int>& r) {
    std::vector<double> x_left(dimension), x_right(dimension), x_mid(dimension);
    for (int i = r.begin(); i != r.end(); ++i) {
        for (size_t j = 0; j < dimension; j++) {
            x_left[j] = a[j] + i * weight[j];
            x_right[j] = a[j] + (i + 1) * weight[j];
            x_mid[j] = (x_left[j] + x_right[j]) / 2;
        }
        res += h * (func(x_left) + 4 * func(x_mid) + func(x_right));
    }
}

void SimpsonCalcul::join(const SimpsonCalcul& sc) {
    res += sc.res;
}

double SimpsonTbb(const std::vector<double>& a, const std::vector<double>& b,
    int n, double(*func)(const std::vector<double>&)) {
    // CHEKS
    if (a.size() != b.size())
        throw("Different dimesions of borders");
    if (a.empty())
        throw("Empty borders");
    if (!(a < b))
        throw("Wrong border format");
    if (n % 2)
        throw("The number of partitions must be even");

    size_t dimension = a.size();
    std::vector<double> weight(dimension);
    double h = 1.0;
    std::vector<double> x_left(dimension);
    std::vector<double> x_right(dimension);
    std::vector<double> x_mid(dimension);

    for (size_t j = 0; j < dimension; j++) {
        weight[j] = (b[j] - a[j]) / static_cast<double>(n);
        h *= b[j] - a[j];
    }

    h *= 1 / static_cast<double>(6.0 * n);

    SimpsonCalcul sc(func, a, weight, dimension, h);
    tbb::parallel_reduce(tbb::blocked_range<int>(0, n), sc);

    return sc.getRes();
}

double SimpsonSeq(const std::vector<double>& a, const std::vector<double>& b,
    int n, double(*func)(const std::vector<double>&)) {
    // CHEKS
    if (a.size() != b.size())
        throw("Different dimesions of borders");
    if (a.empty())
        throw("Empty borders");
    if (!(a < b))
        throw("Wrong border format");
    if (n % 2)
        throw("The number of partitions must be even");

    size_t dimension = a.size();
    double res = 0.0;
    std::vector<double> weight(dimension);
    double h = 1.0;
    std::vector<double> x_left(dimension);
    std::vector<double> x_right(dimension);
    std::vector<double> x_mid(dimension);

    for (size_t j = 0; j < dimension; j++) {
        weight[j] = (b[j] - a[j]) / static_cast<double>(n);
        h *= b[j] - a[j];
    }

    h *= 1 / static_cast<double>(6.0 * n);

    for (int i = 0; i < n; i++) {
        for (size_t j = 0; j < dimension; j++) {
            x_left[j] = a[j] + i * weight[j];
            x_right[j] = a[j] + (i + 1) * weight[j];
            x_mid[j] = (x_left[j] + x_right[j]) / 2;
        }

        res += h * (func(x_left) + 4 * func(x_mid) + func(x_right));
    }
    return res;
}
