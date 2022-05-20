// Copyright 2022 VODENEEV MIKHAIL
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "./jarvis.h"

TEST(Jarvis_test_seq, less_than_minimum_required_size) {
    std::vector<std::pair<double, double>> points = GetPoints(0, 10, 0, 10, 0);
    ASSERT_ANY_THROW(JarvisSeq(points));
}

TEST(Jarvis_test_seq, work_with_the_correct_set_size) {
    std::vector<std::pair<double, double>> points = GetPoints(0, 10, 0, 10, 10);
    ASSERT_NO_THROW(JarvisSeq(points));
}

TEST(Jarvis_test_seq, hull_for_3_points) {
    std::vector<std::pair<double, double>> points = {{1, 1}, {0, 0}, {0, 1}};

    std::vector<std::pair<double, double>> res = JarvisSeq(points);
    std::vector<std::pair<double, double>> expect_set = {{0, 0}, {1, 1}, {0, 1}};

    ASSERT_EQ(res, expect_set);
}

TEST(Jarvis_test_seq, hull_for_5_points) {
    std::vector<std::pair<double, double>> points = {{0, 0}, {0, 4}, {4, 4}, {4, 0}, {2, 2}};

    std::vector<std::pair<double, double>> res = JarvisSeq(points);
    std::vector<std::pair<double, double>> expect_set = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};

    ASSERT_EQ(res, expect_set);
}

TEST(Jarvis_test_seq, hull_for_8_points) {
    std::vector<std::pair<double, double>> points = { {0, 0}, {0, 4}, {4, 4}, {4, 0}, {2, 2},
        {0.5, 0.5}, {1, 1.5}, {1.5, 1}};
    std::vector<std::pair<double, double>> res = JarvisSeq(points);
    std::vector<std::pair<double, double>> expect_set = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};

    ASSERT_EQ(res, expect_set);
}
