// Copyright 2022 Chernyh Daria
#ifndef MODULES_TASK_1_CHERNYH_D_SIMPSON_SIMPSON_H_
#define MODULES_TASK_1_CHERNYH_D_SIMPSON_SIMPSON_H_

#include <vector>

double SimpsonSeq(const std::vector<double>& a, const std::vector<double>& b, unsigned int n,
    double(*func)(const std::vector<double>&));

#endif  // MODULES_TASK_1_CHERNYH_D_SIMPSON_SIMPSON_H_
