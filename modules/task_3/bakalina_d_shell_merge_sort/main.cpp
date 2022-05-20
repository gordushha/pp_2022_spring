// Copyright 2022 Bakalina Darya
#include <gtest/gtest.h>
#include <vector>
#include "./shell_sort_tbb.h"

TEST(Parallel_algorithm, sort_vector_with_shell_sort) {
    int size = 6;
    std::vector<int> v = { 7, 1, 14, 73, 5, 38 };
    std::vector<int> res = { 1, 5, 7, 14, 38, 73 };
    v = shell_sort(v, size);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

TEST(Parallel_algorithm, sort_vector_with_shell_merge_sort) {
    int size = 6;
    std::vector<int> v = { 10, 4, 17, 76, 8, 41 };
    std::vector<int> res = { 4, 8, 10, 17, 41, 76 };
    v = parallel_shell_sort(v, 2);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

TEST(Parallel_algorithm, sort_vectors_with_size_5) {
    int size = 5;
    std::vector<int> v(size);
    std::vector<int> res(size);
    v = create_random_vector(size);
    res = v;
    v = parallel_shell_sort(v, 2);
    res = shell_sort(res, size);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(res[i], v[i]);
    }
}

TEST(Parallel_algorithm, sort_vectors_with_size_10) {
    int size = 10;
    std::vector<int> v(size);
    std::vector<int> res(size);
    v = create_random_vector(size);
    res = v;
    v = parallel_shell_sort(v, 2);
    res = shell_sort(res, size);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(res[i], v[i]);
    }
}

TEST(Parallel_algorithm, vector_with_one_size) {
    std::vector<int> v = { 34 };
    ASSERT_NO_THROW(v = parallel_shell_sort(v, 2));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
