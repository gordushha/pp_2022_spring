// Copyright 2022 Shelepin Nikita
#include <gtest/gtest.h>

#include "./trapezoidal_rule.h"

const double eps = 100;

TEST(TRAPEZOIDAL_RULE_STD, TEST_DIM_1_FUNC_1) {
  std::vector<std::pair<double, double>> limits(2);
  limits = {{-1, 5}};
  int n = 300;
  double seq_result;

  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        return x * x * x;
      };

  const double ref_result = 156;
  seq_result = getParallelTrapezoidal(n, limits, f);

  std::cout << "Par. result: " << seq_result << std::fixed
            << " | Ref. result: " << ref_result << std::fixed
            << " | Error: " << abs(ref_result - seq_result) << std::fixed
            << std::endl;

  ASSERT_NEAR(seq_result, ref_result, eps);
}

TEST(TRAPEZOIDAL_RULE_STD, TEST_DIM_2_FUNC_2) {
  std::vector<std::pair<double, double>> limits(2);
  limits = {{0, 2}, {0, 1}};
  int n = 200;
  double seq_result;

  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        return x + y * y;
      };

  const double ref_result = 2.666;
  seq_result = getParallelTrapezoidal(n, limits, f);

  std::cout << "Par. result: " << seq_result << std::fixed
            << " | Ref. result: " << ref_result << std::fixed
            << " | Error: " << abs(ref_result - seq_result) << std::fixed
            << std::endl;

  ASSERT_NEAR(seq_result, ref_result, eps);
}

TEST(TRAPEZOIDAL_RULE_STD, TEST_DIM_2_FUNC_3) {
  std::vector<std::pair<double, double>> limits(2);
  limits = {{0, 5}, {3, 7}};
  int n = 100;
  double seq_result;

  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        return x + x * y - y;
      };

  const double ref_result = 200;
  seq_result = getParallelTrapezoidal(n, limits, f);

  std::cout << "Par. result: " << seq_result << std::fixed
            << " | Ref. result: " << ref_result << std::fixed
            << " | Error: " << abs(ref_result - seq_result) << std::fixed
            << std::endl;

  ASSERT_NEAR(seq_result, ref_result, eps);
}

TEST(TRAPEZOIDAL_RULE_STD, TEST_DIM_3_FUNC_4) {
  std::vector<std::pair<double, double>> limits(2);
  limits = {{0, 1}, {-4, 2}, {5, 7}};
  int n = 20;
  double seq_result;

  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        double z = vec[2];
        return sin(x) * sin(z) + x * y - z * z * z;
      };

  const double ref_result = -2671.297;
  seq_result = getParallelTrapezoidal(n, limits, f);

  std::cout << "Par. result: " << seq_result << std::fixed
            << " | Ref. result: " << ref_result << std::fixed
            << " | Error: " << abs(ref_result - seq_result) << std::fixed
            << std::endl;

  ASSERT_NEAR(seq_result, ref_result, eps);
}

TEST(TRAPEZOIDAL_RULE_STD, TEST_DIM_3_FUNC_5) {
  std::vector<std::pair<double, double>> limits(2);
  limits = {{1, 3}, {5, 8}, {10, 12}};
  int n = 100;
  double seq_result;

  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        double z = vec[2];
        return exp(sin(x) - cos(y)) / tan(z);
      };

  const double ref_result = -0.1;
  seq_result = getParallelTrapezoidal(n, limits, f);

  std::cout << "Par. result: " << seq_result << std::fixed
            << " | Ref. result: " << ref_result << std::fixed
            << " | Error: " << abs(ref_result - seq_result) << std::fixed
            << std::endl;

  ASSERT_NEAR(seq_result, ref_result, eps);
}
