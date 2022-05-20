// Copyright 2022 Votyakova Daria
#include <gtest/gtest.h>

#include <cmath>

#include "./simpson.h"

TEST(SIMPSON_METHOD_OMP, TEST_FUNCTION_1) {
  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        return x * x - 2 * y;
      };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}});
  std::vector<int> n({100, 100});

  double result = getOMPSimpson(f, limits, n);
  double ref = 293.99;

  double error = 0.01;
  ASSERT_NEAR(result, ref, error);
}

TEST(SIMPSON_METHOD_OMP, TEST_FUNCTION_2) {
  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        double z = vec[2];
        return log10(2 * x * x) + sqrt(z) + 5 * y;
      };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}, {2, 5}});
  std::vector<int> n({10, 10, 10});

  double result = getOMPSimpson(f, limits, n);
  double ref = 203.74;

  double error = 0.01;
  ASSERT_NEAR(result, ref, error);
}

TEST(SIMPSON_METHOD_OMP, TEST_FUNCTION_3) {
  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        double z = vec[2];
        return x * y * z;
      };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}, {4, 5}});
  std::vector<int> n({10, 5, 5});

  double result = getOMPSimpson(f, limits, n);
  double ref = 283.50;

  double error = 0.1;
  ASSERT_NEAR(result, ref, error);
}

TEST(SIMPSON_METHOD_OMP, TEST_FUNCTION_4) {
  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        double z = vec[2];
        return exp(x) - sqrt(10) * 5 * sin(y) + cos(-2 * z * z);
      };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}, {0, 5}});
  std::vector<int> n({10, 5, 5});

  double result = getOMPSimpson(f, limits, n);
  double ref = 109420.49;

  double error = 0.01;
  ASSERT_NEAR(result, ref, error);
}

TEST(SIMPSON_METHOD_OMP, TEST_FUNCTION_5) {
  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        double z = vec[2];
        double t = vec[3];
        return cos(5 * x) + exp(y) + 2.9 * sin(z) - t * t;
      };

  std::vector<std::pair<double, double>> limits(
      {{4, 10}, {1, 2}, {1, 5}, {6, 10}});
  std::vector<int> n({5, 5, 3, 2});

  double result = getOMPSimpson(f, limits, n);
  double ref = -5832.64;

  double error = 0.01;
  ASSERT_NEAR(result, ref, error);
}
