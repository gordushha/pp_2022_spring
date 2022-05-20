// Copyright 2022 Bakalina Darya
#include <gtest/gtest.h>
#include <vector>
#include "../../../3rdparty/unapproved/unapproved.h"
#include "./shell_sort_std.h"

TEST(Parallel_algorithm, sort_vector_with_shell_merge_sort) {
    int size = 6;
    std::vector<int> v = { 20, 14, 27, 96, 18, 51 };
    std::vector<int> res = { 14, 18, 20, 27, 51, 96 };
    v = parallel_shell_sort(v, 2);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

TEST(Parallel_algorithm, sort_vector_with_shell_sort) {
    int size = 6;
    std::vector<int> v = { 6, 5, 4, 3, 2, 1 };
    std::vector<int> res = { 1, 2, 3, 4, 5, 6 };
    v = shell_sort(v);
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
    res = shell_sort(res);
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
    res = shell_sort(res);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(res[i], v[i]);
    }
}

TEST(Parallel_algorithm, vector_with_one_size) {
    std::vector<int> v = { 34 };
    ASSERT_NO_THROW(v = parallel_shell_sort(v, 2));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
