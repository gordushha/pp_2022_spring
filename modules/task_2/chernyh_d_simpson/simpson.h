// Copyright 2022 Chernyh Daria
#ifndef MODULES_TASK_2_CHERNYH_D_SIMPSON_SIMPSON_H_
#define MODULES_TASK_2_CHERNYH_D_SIMPSON_SIMPSON_H_

#include <omp.h>
#include <vector>

double SimpsonOmp(const std::vector<double>& a, const std::vector<double>& b,
    int n, double(*func)(const std::vector<double>&));

#endif  // MODULES_TASK_2_CHERNYH_D_SIMPSON_SIMPSON_H_
