// Copyright 2022 Bakalina Darya
#include <omp.h>
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

#include "../../../modules/task_2/bakalina_d_shell_merge_sort_omp/shell_sort_omp.h"

std::vector<int> create_random_vector(int size_n) {
    if (size_n <= 0) {
        throw "Wrong size";
    }
    std::vector <int> v(size_n);
    std::random_device dev;
    std::mt19937 gen(dev());
    for (int i = 0; i < size_n; ++i) {
        v[i] = gen() % 100;
    }
    return v;
}

bool check_equality(std::vector<int> v1, std::vector<int> v2) {
    bool flag = 0;
    int size = v1.size();
    if (v1.size() != v2.size()) {
        throw "Vector sizes do not match";
    }
    for (int i = 0; i < size; i++) {
        if (v1[i] == v2[i]) {
            flag = 1;
        }
    }
    return flag;
}

void print_vector(std::vector<int> vector, int size) {
    if (size <= 0) {
        throw "Wrong size";
    }
    for (int i = 0; i < size; ++i) {
        std::cout << vector[i] << std::endl;
    }
}

std::vector<int> merge_two_vector(std::vector<int> vctr_1, std::vector<int> vctr_2) {
    int i = 0;
    int j = 0;
    int k = 0;
    int size_1 = vctr_1.size();
    int size_2 = vctr_2.size();
    std::vector<int> res(size_1 + size_2);
    while (size_1 && size_2) {
        if (vctr_1[i] < vctr_2[j]) {
            res[k] = vctr_1[i];
            i++;
            size_1--;
        } else {
            res[k] = vctr_2[j];
            j++;
            size_2--;
        }
        k++;
    }
    if (size_1 == 0) {
        for (int l = j; l < j + size_2; l++) {
            res[k] = vctr_2[l];
            k++;
        }
    } else if (size_2 == 0) {
        for (int m = i; m < i + size_1; m++) {
            res[k] = vctr_1[m];
            k++;
        }
    }
    return res;
}

std::vector <int> lin_shell_sort(const std::vector <int>& v) {
    int iter = 0;
    int i = 0;
    int j = 0;
    int tmp = 0;
    int size_n = v.size();
    if (size_n < 1) {
        throw "Wrong size";
    }
    std::vector <int> res(v);
    for (iter = size_n / 2; iter > 0; iter /= 2) {
        for (i = iter; i < size_n; i++) {
            for (j = i - iter; j >= 0 && res[j] > res[j + iter]; j -= iter) {
                tmp = res[j];
                res[j] = res[j + iter];
                res[j + iter] = tmp;
            }
        }
    }
    return res;
}

std::vector <int> parallel_shell_sort(std::vector<int> vctr, std::size_t num_threads, int size) {
    if (size < 1) {
        throw "Wrong size";
    }
    if (size == 1) {
        return vctr;
    }
    omp_set_num_threads(num_threads);
    std::vector<int> res(size);
    std::size_t quotient = vctr.size() / num_threads;
    std::size_t residue = vctr.size() % num_threads;
    std::vector<int> tmp_res;
#pragma omp parallel shared(vctr, residue) private(tmp_res)
    {
        std::size_t tid = omp_get_thread_num();
        if (tid == 0) {
            tmp_res.resize(quotient + residue);
            std::copy(vctr.begin(), vctr.begin() + quotient + residue, tmp_res.begin());
        } else {
            tmp_res.resize(quotient);
        }
        for (std::size_t i = 1; i < num_threads; i++) {
            if (tid == i) {
                std::copy(vctr.begin() + quotient * i + residue, vctr.end() - quotient * (num_threads - i - 1),
                    tmp_res.begin());
            }
        }
        tmp_res = lin_shell_sort(tmp_res);
#pragma omp master
        res = tmp_res;
#pragma omp barrier
#pragma omp critical
        if (tid != 0) {
            res = merge_two_vector(tmp_res, res);
        }
    }
    return res;
}
