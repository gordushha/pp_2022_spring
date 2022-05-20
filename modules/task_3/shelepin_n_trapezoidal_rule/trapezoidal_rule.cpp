// Copyright 2022 Shelepin Nikita
#include "../../../modules/task_3/shelepin_n_trapezoidal_rule/trapezoidal_rule.h"

#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>

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

  auto result = tbb::parallel_reduce(
      tbb::blocked_range<int>(0, count), 0.0,
      [&](tbb::blocked_range<int> r, double running_total) {
        for (int j = r.begin(); j < r.end(); ++j) {
          std::vector<double> combinations(dimension);
          for (int i = 0; i < dimension; i++) {
            combinations[i] = limits[i].first + (j % n) * h[i] + h[i] * 0.5;
          }
          running_total += f(combinations);
        }

        return running_total;
      },
      std::plus<double>());

  for (int i = 0; i < dimension; i++) {
    result *= h[i];
  }

  return result;
}
