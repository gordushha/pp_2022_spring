// Copyright 2022 Chernyh Daria
#include <gtest/gtest.h>
#include <iostream>
#include <cmath>
#include "./simpson.h"

double func_1(const std::vector<double>& x) {
    return x[0];
}

double func_2(const std::vector<double>& x) {
    return sin(x[0]) + cos(x[1]);
}

double func_3(const std::vector<double>& x) {
    return x[0] * x[0] + x[1] * x[1] + x[2] * x[2];
}

double func_4(const std::vector<double>& x) {
    return x[0] * x[0] + x[1] + cos(x[2]) + pow(x[3], 3);
}

TEST(Simpson_test_omp, different_dimesions) {
    std::vector<double> a = { 5.0 };
    std::vector<double> b = { 6.0, 2.0 };
    unsigned int n = 10;
    omp_set_num_threads(1);

    ASSERT_ANY_THROW(SimpsonOmp(a, b, n, func_1));
}

TEST(Simpson_test_omp, empty_borders) {
    std::vector<double> a = {};
    std::vector<double> b = {};
    unsigned int n = 10;
    omp_set_num_threads(1);

    ASSERT_ANY_THROW(SimpsonOmp(a, b, n, func_1));
}

TEST(Simpson_test_omp, wrong_format) {
    std::vector<double> a = { 5.0 };
    std::vector<double> b = { -1.0 };
    unsigned int n = 10;
    omp_set_num_threads(1);

    ASSERT_ANY_THROW(SimpsonOmp(a, b, n, func_1));
}

TEST(Simpson_test_omp, wrong_number_of_splitting) {
    std::vector<double> a = { 0.0 };
    std::vector<double> b = { 1.0 };
    unsigned int n = 5;
    omp_set_num_threads(1);

    ASSERT_ANY_THROW(SimpsonOmp(a, b, n, func_1));
}

TEST(Simpson_test_omp, func_of_one_dimensions) {
    std::vector<double> a = { 0.0 };
    std::vector<double> b = { 4.0 };
    unsigned int steps = 100;

    omp_set_num_threads(2);

    double res = SimpsonOmp(a, b, steps, func_1);

    ASSERT_NEAR(res, 8.0, 0.1);
}

TEST(Simpson_test_omp, func_of_two_dimensions) {
    std::vector<double> a = { -1.0, 0.0 };
    std::vector<double> b = { 2.0, 4.0 };
    unsigned int steps = 100;

    omp_set_num_threads(2);

    double res = SimpsonOmp(a, b, steps, func_2);

    ASSERT_NEAR(res, 1.55538, 0.1);
}

TEST(Simpson_test_omp, func_of_three_dimensions) {
    std::vector<double> a = { 0.0, 1.0, -2.0 };
    std::vector<double> b = { 3.0, 5.0, 0.0 };
    unsigned int steps = 400;

    omp_set_num_threads(2);

    double res = SimpsonOmp(a, b, steps, func_3);

    ASSERT_NEAR(res, 352.0, 0.1);
}

TEST(Simpson_test_omp, func_of_four_dimensions) {
    std::vector<double> a = { 0.0, -1.0, 0.0, -2.0 };
    std::vector<double> b = { 1.0, 2.0, 2.0, 1.0 };
    unsigned int steps = 400;

    omp_set_num_threads(2);

    double res = SimpsonOmp(a, b, steps, func_4);

    ASSERT_NEAR(res, 0.68367, 0.1);
}

/*
TEST(Simpson_test_omp, _time) {
    std::vector<double> a = { 0.0, -1.0, 0.0, -2.0 };
    std::vector<double> b = { 1.0, 2.0, 2.0, 1.0 };
    unsigned int steps = 10000;
    int thread = 6;

    omp_set_num_threads(1);

    double t_s = omp_get_wtime();
    double res = SimpsonOmp(a, b, steps, func_4);
    double t_f = omp_get_wtime();

    std::cout << " Seq_time= " << t_f - t_s << std::endl;

    omp_set_num_threads(thread);

    t_s = omp_get_wtime();
    res = SimpsonOmp(a, b, steps, func_4);
    t_f = omp_get_wtime();

    std::cout << " Omp_time= " << t_f - t_s << " Num_thread= " << thread << std::endl;

    ASSERT_NEAR(res, 0.68367, 0.1);
}*/
