// Copyright 2022 Shelepin Nikita
#include "../../../modules/task_4/shelepin_n_trapezoidal_rule/trapezoidal_rule.h"

const int THREADS = 8;

double getParallelTrapezoidal(
    const int n, const std::vector<std::pair<double, double>>& limits,
    const std::function<double(std::vector<double>)>& f) {
  int dimension = static_cast<int>(limits.size());
  int count = 1;
  std::vector<double> h(dimension);
  for (int i = 0; i < dimension; i++) {
    h[i] = (limits[i].second - limits[i].first) / n;
    count = count * n;
  }

  auto total_result = 0.0;
  std::vector<double> local_result(THREADS, 0.0);

  auto worker = [&dimension, &limits, &n, &h, &f, &local_result](
                    int begin, int end, int ind) {
    for (int j = begin; j < end; ++j) {
      std::vector<double> combinations(dimension);
      for (int i = 0; i < dimension; i++) {
        combinations[i] = limits[i].first + (j % n) * h[i] + h[i] * 0.5;
      }
      local_result[ind] += f(combinations);
    }
  };

  // parallel
  std::vector<std::thread> threads(THREADS);
  const int grainsize = count / THREADS;

  auto work_iter = 0;
  int counter = 0;
  for (auto it = std::begin(threads); it != std::end(threads) - 1; ++it) {
    *it = std::thread(worker, work_iter, work_iter + grainsize, counter);
    work_iter += grainsize;
    counter++;
  }
  threads.back() = std::thread(worker, work_iter, count, counter);

  for (auto&& i : threads) {
    i.join();
  }

  for (auto val : local_result) {
    total_result += val;
  }

  for (int i = 0; i < dimension; i++) {
    total_result *= h[i];
  }

  return total_result;
}
