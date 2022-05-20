// Copyright 2022 Bakalina Darya
#ifndef MODULES_TASK_4_BAKALINA_D_SHELL_MERGE_SORT_SHELL_SORT_STD_H_
#define MODULES_TASK_4_BAKALINA_D_SHELL_MERGE_SORT_SHELL_SORT_STD_H_

#include <vector>

std::vector<int> create_random_vector(int size_n);
void print_vector(std::vector<int> vector, int size);
bool check_equality(std::vector<int> v1, std::vector<int> v2);
std::vector<std::vector<int>> partition(const std::vector<int>& vctr, std::size_t num_threads);
std::vector<int> merge_two_vector(std::vector<int> vctr_1, std::vector<int> vctr_2);
std::vector <int> shell_sort(const std::vector <int>& v);
std::vector <int> lin_shell_sort(std::vector<int> vctr, int size);
std::vector <int> parallel_shell_sort(std::vector<int> vec, std::size_t num_threads);

#endif  // MODULES_TASK_4_BAKALINA_D_SHELL_MERGE_SORT_SHELL_SORT_STD_H_
