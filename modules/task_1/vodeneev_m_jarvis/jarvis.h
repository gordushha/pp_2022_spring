// Copyright 2022 VODENEEV MIKHAIL
#ifndef MODULES_TASK_1_VODENEEV_M_JARVIS_JARVIS_H_
#define MODULES_TASK_1_VODENEEV_M_JARVIS_JARVIS_H_
#include <random>
#include <utility>
#include <vector>

std::vector<std::pair<double, double>> GetPoints(int left_border, int right_border,
    int low_border, int high_border, size_t size);

double OrientationPointRelativeToVector(std::pair<double, double> A,
    std::pair<double, double> B, std::pair<double, double> point);

std::vector<std::pair<double, double>> JarvisSeq(std::vector<std::pair
    <double, double>> points);

#endif  // MODULES_TASK_1_VODENEEV_M_JARVIS_JARVIS_H_
