// Copyright 2022 Shelepin Nikita
#include "../../../modules/task_2/shelepin_n_trapezoidal_rule/trapezoidal_rule.h"

#include <omp.h>

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

  double result = 0.0;

#pragma omp parallel
#pragma omp for schedule(static, 1) reduction(+ : result)
  for (int j = 0; j < count; j++) {
    std::vector<double> combinations(dimension);
    for (int i = 0; i < dimension; i++) {
      combinations[i] = limits[i].first + (j % n) * h[i] + h[i] * 0.5;
    }
    result += f(combinations);
  }

  for (int i = 0; i < dimension; i++) {
    result *= h[i];
  }

  return result;
}
