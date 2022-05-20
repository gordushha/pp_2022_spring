// Copyright 2022 Chernyh Daria
#include"../../../modules/task_1/chernyh_d_simpson/simpson.h"

double SimpsonSeq(const std::vector<double>& a, const std::vector<double>& b, unsigned int n,
    double(*func)(const std::vector<double>&)) {
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

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < dimension; j++) {
            x_left[j] = a[j] + i * weight[j];
            x_right[j] = a[j] + (i + 1) * weight[j];
            x_mid[j] = (x_left[j] + x_right[j]) / 2;
        }
        res += h * (func(x_left) + 4 * func(x_mid) + func(x_right));
    }
    return res;
}
