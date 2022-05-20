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

TEST(Simpson_test_seq, different_dimesions) {
    std::vector<double> a = { 0.0 };
    std::vector<double> b = { 1.0, 2.0 };
    unsigned int n = 10;

    ASSERT_ANY_THROW(SimpsonSeq(a, b, n, func_1));
}

TEST(Simpson_test_seq, empty_borders) {
    std::vector<double> a = {};
    std::vector<double> b = {};
    unsigned int n = 10;

    ASSERT_ANY_THROW(SimpsonSeq(a, b, n, func_1));
}

TEST(Simpson_test_seq, wrong_format) {
    std::vector<double> a = { 0.0 };
    std::vector<double> b = { -1.0};
    unsigned int n = 10;

    ASSERT_ANY_THROW(SimpsonSeq(a, b, n, func_1));
}

TEST(Simpson_test_seq, wrong_number_of_splitting) {
    std::vector<double> a = { 0.0 };
    std::vector<double> b = { 1.0};
    unsigned int n = 5;

    ASSERT_ANY_THROW(SimpsonSeq(a, b, n, func_1));
}

TEST(Simpson_test_seq, func__of_one_dimensions) {
    std::vector<double> a = { 0.0 };
    std::vector<double> b = { 4.0 };
    unsigned int steps = 100;

    double res = SimpsonSeq(a, b, steps, func_1);

    ASSERT_NEAR(res, 8.0, 0.1);
}

TEST(Simpson_test_seq, func_of_two_dimensions) {
    std::vector<double> a = { -1.0, 0.0 };
    std::vector<double> b = { 2.0, 4.0 };
    unsigned int steps = 100;

    double res = SimpsonSeq(a, b, steps, func_2);

    ASSERT_NEAR(res, 1.55538, 0.1);
}

TEST(Simpson_test_seq, func__of_three_dimensions) {
    std::vector<double> a = { 0.0, 1.0, -2.0 };
    std::vector<double> b = { 3.0, 5.0, 0.0 };
    unsigned int steps = 400;

    double res = SimpsonSeq(a, b, steps, func_3);

    ASSERT_NEAR(res, 352.0, 0.1);
}
