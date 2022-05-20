// Copyright 2022 VODENEEV MIKHAIL
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "./jarvis.h"


TEST(Jarvis_test_omp, less_than_minimum_required_size) {
    std::vector<std::pair<double, double>> points = GetPoints(0, 10, 0, 10, 0);
    ASSERT_ANY_THROW(JarvisOmp(points, 4));
}

TEST(Jarvis_test_omp, work_with_the_correct_set_size) {
    std::vector<std::pair<double, double>> points = GetPoints(0, 10, 0, 10, 10);
    ASSERT_NO_THROW(JarvisOmp(points, 8));
}

TEST(Jarvis_test_omp, hull_for_3_points) {
    std::vector<std::pair<double, double>> points = { {1, 1}, {0, 0}, {0, 1} };

    std::vector<std::pair<double, double>> res = JarvisOmp(points, 4);
    std::vector<std::pair<double, double>> expect_set = { {0, 0}, {1, 1}, {0, 1} };

    ASSERT_EQ(res, expect_set);
}

TEST(Jarvis_test_omp, hull_for_5_points) {
    std::vector<std::pair<double, double>> points = { {0, 0}, {0, 4}, {4, 4}, {4, 0}, {2, 2} };

    std::vector<std::pair<double, double>> res = JarvisOmp(points, 6);
    std::vector<std::pair<double, double>> expect_set = { {0, 0}, {4, 0}, {4, 4}, {0, 4} };

    ASSERT_EQ(res, expect_set);
}

TEST(Jarvis_test_omp, hull_for_8_points) {
    std::vector<std::pair<double, double>> points = { {0, 0}, {0, 4}, {4, 4}, {4, 0}, {2, 2},
        {0.5, 0.5}, {1, 1.5}, {1.5, 1} };
    std::vector<std::pair<double, double>> res = JarvisOmp(points, 4);
    std::vector<std::pair<double, double>> expect_set = { {0, 0}, {4, 0}, {4, 4}, {0, 4} };

    ASSERT_EQ(res, expect_set);
}

TEST(Jarvis_test_omp, compare_seq_and_omp_1000_points) {
    std::vector<std::pair<double, double>> points = GetPoints(-1000, 1000, -1000, 1000, 1000);
    double start_seq = omp_get_wtime();
    std::vector<std::pair<double, double>> res_seq = JarvisSeq(points);
    double end_seq = omp_get_wtime();
    double start_omp = omp_get_wtime();
    std::vector<std::pair<double, double>> res_omp = JarvisOmp(points, 6);
    double end_omp = omp_get_wtime();


    std::cout << "Time seq: " << end_seq - start_seq << std::endl;
    std::cout << "Time omp: " << end_omp - start_omp << std::endl;

    ASSERT_EQ(res_omp, res_seq);
}

TEST(Jarvis_test_omp, compare_seq_and_omp_10000_points) {
    std::vector<std::pair<double, double>> points = GetPoints(-1000, 1000, -1000, 1000, 10000);
    double start_seq = omp_get_wtime();
    std::vector<std::pair<double, double>> res_seq = JarvisSeq(points);
    double end_seq = omp_get_wtime();
    double start_omp = omp_get_wtime();
    std::vector<std::pair<double, double>> res_omp = JarvisOmp(points, 6);
    double end_omp = omp_get_wtime();


    std::cout << "Time seq: " << end_seq - start_seq << std::endl;
    std::cout << "Time omp: " << end_omp - start_omp << std::endl;

    ASSERT_EQ(res_omp, res_seq);
}

TEST(Jarvis_test_omp, compare_seq_and_omp_100000_points) {
    std::vector<std::pair<double, double>> points = GetPoints(-1000, 1000, -1000, 1000, 100000);
    double start_seq = omp_get_wtime();
    std::vector<std::pair<double, double>> res_seq = JarvisSeq(points);
    double end_seq = omp_get_wtime();
    double start_omp = omp_get_wtime();
    std::vector<std::pair<double, double>> res_omp = JarvisOmp(points, 6);
    double end_omp = omp_get_wtime();


    std::cout << "Time seq: " << end_seq - start_seq << std::endl;
    std::cout << "Time omp: " << end_omp - start_omp << std::endl;

    ASSERT_EQ(res_omp, res_seq);
}

