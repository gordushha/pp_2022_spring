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

TEST(Simpson_test_tbb, different_dimesions) {
    std::vector<double> a = { 5.0 };
    std::vector<double> b = { 6.0, 2.0 };
    unsigned int n = 10;

    ASSERT_ANY_THROW(SimpsonTbb(a, b, n, func_1));
}

TEST(Simpson_test_tbb, empty_borders) {
    std::vector<double> a = {};
    std::vector<double> b = {};
    unsigned int n = 10;

    ASSERT_ANY_THROW(SimpsonTbb(a, b, n, func_1));
}

TEST(Simpson_test_tbb, wrong_format) {
    std::vector<double> a = { 5.0 };
    std::vector<double> b = { -1.0 };
    unsigned int n = 10;

    ASSERT_ANY_THROW(SimpsonTbb(a, b, n, func_1));
}

TEST(Simpson_test_tbb, wrong_number_of_splitting) {
    std::vector<double> a = { 0.0 };
    std::vector<double> b = { 1.0 };
    unsigned int n = 5;

    ASSERT_ANY_THROW(SimpsonTbb(a, b, n, func_1));
}

TEST(Simpson_test_tbb, func_of_one_dimensions) {
    std::vector<double> a = { 0.0 };
    std::vector<double> b = { 4.0 };
    unsigned int n = 30;

    double res_par = SimpsonTbb(a, b, n, func_1);

    ASSERT_NEAR(res_par, 8.0, 0.1);
}

TEST(Simpson_test_tbb, func_of_two_dimensions) {
    std::vector<double> a = { -1.0, 0.0 };
    std::vector<double> b = { 2.0, 4.0 };
    unsigned int n = 100;

    double res_par = SimpsonTbb(a, b, n, func_2);

    ASSERT_NEAR(res_par, 1.55538, 0.1);
}

TEST(Simpson_test_tbb, func_of_three_dimensions) {
    std::vector<double> a = { 0.0, 1.0, -2.0 };
    std::vector<double> b = { 3.0, 5.0, 0.0 };
    unsigned int n = 100;

    double res_par = SimpsonTbb(a, b, n, func_3);

    ASSERT_NEAR(res_par, 352.0, 0.1);
}

TEST(Simpson_test_tbb, func_of_four_dimensions) {
    std::vector<double> a = { 0.0, -1.0, 0.0, -2.0 };
    std::vector<double> b = { 1.0, 2.0, 2.0, 1.0 };
    unsigned int n = 100;

    double res_par = SimpsonTbb(a, b, n, func_4);

    ASSERT_NEAR(res_par, 0.68367, 0.1);
}

/*
TEST(Simpson_test_tbb, _time) {
   std::vector<double> a = { 0.0, 1.0, -2.0 };
    std::vector<double> b = { 3.0, 5.0, 0.0 };
    unsigned int n = 100;

    double res_seq, res_par;

    tbb::tick_count t_s = tbb::tick_count::now();
    tbb::task_arena arena(1);
    arena.execute([&] {res_seq = SimpsonSeq(a, b, n, func_3); });

    double t_seq = (tbb::tick_count::now() - t_s).seconds();

    std::cout << " Seq_time= " << t_seq << std::endl;

    t_s = tbb::tick_count::now();
    arena = tbb::task_arena(2);
    arena.execute([&] {res_par = SimpsonTbb(a, b, n, func_3); });

    double t_tbb = (tbb::tick_count::now() - t_s).seconds();

    std::cout << " Tbb_time= " << std::endl;
    std::cout << "T_seq/T_tbb= " << t_seq/t_tbb << std::endl;

    ASSERT_NEAR(res_par, 352.0, 0.1);
}*/

