// Copyright 2022 Votyakova Daria
#ifndef MODULES_TASK_1_VOTYAKOVA_D_SIMPSON_SIMPSON_H_
#define MODULES_TASK_1_VOTYAKOVA_D_SIMPSON_SIMPSON_H_

#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

double getSeqSimpson(
    const std::function<double(std::vector<double>)>& f,
    const std::vector<std::pair<double, double>>& limits,
    const std::vector<int>& n);

#endif  // MODULES_TASK_1_VOTYAKOVA_D_SIMPSON_SIMPSON_H_
