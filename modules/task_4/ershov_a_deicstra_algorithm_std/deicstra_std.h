// Copyright 2022 Ershov Aleksey
#ifndef MODULES_TASK_4_ERSHOV_A_DEICSTRA_ALGORITHM_STD_DEICSTRA_STD_H_
#define MODULES_TASK_4_ERSHOV_A_DEICSTRA_ALGORITHM_STD_DEICSTRA_STD_H_

#include <string>
#include <vector>

std::vector<std::vector<int>> getRandomVector(const int count);

std::vector<int> getDeicstra(const std::vector<std::vector<int>>& graf,
                             const int top);

std::vector<int> getSequentialDeicstra(
    const std::vector<std::vector<int>>& graf);

void getThreadIteration(const std::vector<std::vector<int>>& graf,
                        const int start, const int numTops,
                        std::vector<int>* result);

std::vector<int> getParallelDeicstra(const std::vector<std::vector<int>>& graf);

#endif  // MODULES_TASK_4_ERSHOV_A_DEICSTRA_ALGORITHM_STD_DEICSTRA_STD_H_
