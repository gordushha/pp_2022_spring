// Copyright 2022 Votyakova Daria
#include "../../../modules/task_2/votyakova_d_simpson/simpson.h"

#include <omp.h>

#include <cmath>

double getOMPSimpson(const std::function<double(std::vector<double>)>& f,
                     const std::vector<std::pair<double, double>>& limits,
                     const std::vector<int>& n) {
  int dim = n.size();
  std::vector<double> h(dim);
  int64_t counter = 1;
  for (int i = 0; i < dim; ++i) {
    h[i] = (limits[i].second - limits[i].first) / n[i];
    counter *= n[i];
  }
  double result = 0;

#pragma omp parallel
#pragma omp for schedule(static, 1) reduction(+ : result)
  for (int i = 0; i < counter; ++i) {
    std::vector<std::vector<double>> params(dim);
    int temp = i;
    for (int j = 0; j < dim; ++j) {
      params[j].push_back(limits[j].first + temp % n[j] * h[j]);
      params[j].push_back(limits[j].first + temp % n[j] * h[j] + h[j] / 2);
      params[j].push_back(limits[j].first + temp % n[j] * h[j] + h[j] / 2);
      params[j].push_back(limits[j].first + temp % n[j] * h[j] + h[j] / 2);
      params[j].push_back(limits[j].first + temp % n[j] * h[j] + h[j] / 2);
      params[j].push_back(limits[j].first + temp % n[j] * h[j] + h[j]);
      temp /= n[j];
    }
    std::vector<double> point;
    for (int i = 0; i < pow(6, dim); ++i) {
      int temp = i;
      for (int j = 0; j < dim; ++j) {
        point.push_back(params[j][temp % 6]);
        temp /= 6;
      }
      result += f(point);
      point.clear();
    }
    params.clear();
  }
  for (int i = 0; i < dim; ++i) {
    result *= h[i] / 6.0;
  }
  return result;
}
