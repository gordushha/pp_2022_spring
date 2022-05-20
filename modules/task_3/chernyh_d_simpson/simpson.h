// Copyright 2022 Chernyh Daria
#ifndef MODULES_TASK_3_CHERNYH_D_SIMPSON_SIMPSON_H_
#define MODULES_TASK_3_CHERNYH_D_SIMPSON_SIMPSON_H_

#include <tbb/tbb.h>
#include <vector>

class SimpsonCalcul {
    double(*func)(const std::vector<double>&);
    const std::vector<double>& a;
    const std::vector<double>& weight;
    size_t dimension;
    const double h;
    double res;

 public :
    explicit SimpsonCalcul(double(*func)(const std::vector<double>&),
        const std::vector<double>& a, const std::vector<double>& weight,
        size_t dimension, const double h)
        :func(func), a(a), weight(weight), dimension(dimension), h(h), res(0)
    {}

    SimpsonCalcul(const SimpsonCalcul& sc, tbb::split):
        func(sc.func), a(sc.a), weight(sc.weight), dimension(sc.dimension),
        h(sc.h), res(0)
    {}

    void operator() (const tbb::blocked_range<int>& r);

    void join(const SimpsonCalcul& sc);

    double getRes() {
        return res;
    }
};

double SimpsonTbb(const std::vector<double>& a, const std::vector<double>& b,
    int n, double(*func)(const std::vector<double>&));
double SimpsonSeq(const std::vector<double>& a, const std::vector<double>& b,
    int n, double(*func)(const std::vector<double>&));

#endif  // MODULES_TASK_3_CHERNYH_D_SIMPSON_SIMPSON_H_
