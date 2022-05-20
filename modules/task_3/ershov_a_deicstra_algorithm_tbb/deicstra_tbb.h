// Copyright 2022 Ershov Aleksey
#ifndef MODULES_TASK_3_ERSHOV_A_DEICSTRA_ALGORITHM_TBB_DEICSTRA_TBB_H_
#define MODULES_TASK_3_ERSHOV_A_DEICSTRA_ALGORITHM_TBB_DEICSTRA_TBB_H_

#include <tbb/tbb.h>

#include <string>
#include <vector>

class Deicstor {
 private:
  const std::vector<std::vector<int>>& graf;
  std::vector<int>* result;

 public:
  Deicstor(const std::vector<std::vector<int>>& _graf,
           std::vector<int>* _result)
      : graf(_graf), result(_result) {}

  void operator()(const tbb::blocked_range<int>& r) const;
};

std::vector<std::vector<int>> getRandomVector(const int count);

std::vector<int> getDeicstra(const std::vector<std::vector<int>>& graf,
                             const int top);

std::vector<int> getSequentialDeicstra(
    const std::vector<std::vector<int>>& graf);

std::vector<int> getParallelDeicstra(const std::vector<std::vector<int>>& graf);

#endif  // MODULES_TASK_3_ERSHOV_A_DEICSTRA_ALGORITHM_TBB_DEICSTRA_TBB_H_
