// Copyright 2022 Bakalina Darya
#ifndef MODULES_TASK_2_BAKALINA_D_SHELL_MERGE_SORT_OMP_SHELL_SORT_OMP_H_
#define MODULES_TASK_2_BAKALINA_D_SHELL_MERGE_SORT_OMP_SHELL_SORT_OMP_H_
#include <vector>

std::vector<int> create_random_vector(int size_n);
void print_vector(std::vector<int> vector, int size);
bool check_equality(std::vector<int> v1, std::vector<int> v2);
std::vector<int> merge_two_vector(std::vector<int> vctr_1, std::vector<int> vctr_2);
std::vector <int> lin_shell_sort(const std::vector <int>& v);
std::vector <int> parallel_shell_sort(std::vector<int> vec, std::size_t nthreads, int size);

#endif  // MODULES_TASK_2_BAKALINA_D_SHELL_MERGE_SORT_OMP_SHELL_SORT_OMP_H_
