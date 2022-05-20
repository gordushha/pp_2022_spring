// Copyright 2022 Shelepin Nikita
#include "../../../modules/task_1/shelepin_n_trapezoidal_rule/trapezoidal_rule.h"

double getSequentialTrapezoidal(
    const int n, const std::vector<std::pair<double, double>>& limits,
    const std::function<double(std::vector<double>)>& f) {
  int dimension = static_cast<int>(limits.size());
  size_t count = 1;
  std::vector<double> h(dimension);
  for (int i = 0; i < dimension; i++) {
    h[i] = (limits[i].second - limits[i].first) / n;
    count = count * n;
  }

  double result = 0.0;
  std::vector<double> combinations(dimension);
  for (size_t j = 0; j < count; j++) {
    for (int i = 0; i < dimension; i++) {
      // printf("%f\n", (j % n) * h[i]);
      combinations[i] = limits[i].first + (j % n) * h[i] + h[i] * 0.5;
    }
    result += f(combinations);
  }

  for (int i = 0; i < dimension; i++) {
    result *= h[i];
  }

  return result;
}
