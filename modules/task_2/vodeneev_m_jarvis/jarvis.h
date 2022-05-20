// Copyright 2022 VODENEEV MIKHAIL
#ifndef MODULES_TASK_2_VODENEEV_M_JARVIS_JARVIS_H_
#define MODULES_TASK_2_VODENEEV_M_JARVIS_JARVIS_H_

#include <omp.h>

#include <random>
#include <algorithm>
#include <utility>
#include <vector>

std::vector<std::pair<double, double>> GetPoints(int left_border, int right_border,
    int low_border, int high_border, size_t size);

double OrientationPointRelativeToVector(std::pair<double, double> A,
    std::pair<double, double> B, std::pair<double, double> point);

std::vector<std::pair<double, double>> JarvisSeq(std::vector<std::pair
    <double, double>> points);

std::vector<std::pair<double, double>> JarvisOmp(std::vector<std::pair
    <double, double>> points, int numthreads);

#endif  // MODULES_TASK_2_VODENEEV_M_JARVIS_JARVIS_H_
