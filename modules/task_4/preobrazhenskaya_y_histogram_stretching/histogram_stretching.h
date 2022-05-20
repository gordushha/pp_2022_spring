// Copyright 2022 Preobrazhenskaya Yuliya
#ifndef MODULES_TASK_4_PREOBRAZHENSKAYA_Y_HISTOGRAM_STRETCHING_HISTOGRAM_STRETCHING_H_
#define MODULES_TASK_4_PREOBRAZHENSKAYA_Y_HISTOGRAM_STRETCHING_HISTOGRAM_STRETCHING_H_

#include <vector>
#include <iostream>

std::vector<int> getRandomImage(int height, int width);
int getYmax(std::vector<int> image, int height, int width);
int getYmin(std::vector<int> image, int height, int width);
std::vector<int> getSequentialOperations(std::vector<int> image,
    int height, int width, int y_max, int y_min);
std::vector<int> getParallelOperationsSTD(std::vector<int> image,
    int height, int width, int y_max, int y_min);

#endif  // MODULES_TASK_4_PREOBRAZHENSKAYA_Y_HISTOGRAM_STRETCHING_HISTOGRAM_STRETCHING_H_
