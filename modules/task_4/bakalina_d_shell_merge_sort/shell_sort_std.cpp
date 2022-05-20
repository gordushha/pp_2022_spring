// Copyright 2022 Bakalina Darya
#include <vector>
#include <utility>
#include <random>
#include <algorithm>
#include <iostream>
#include "../../../modules/task_4/bakalina_d_shell_merge_sort/shell_sort_std.h"
#include "../../../3rdparty/unapproved/unapproved.h"

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

std::vector<std::vector<int>> partition(const std::vector<int>& vctr, std::size_t num_threads) {
    if (num_threads <= 0) {
        throw "Invalid number of threads";
    }
    std::vector<std::vector<int>> res;
    size_t interval = vctr.size() / num_threads;
    size_t residue = vctr.size() % num_threads;
    size_t start = 0, finish = 0;
    for (size_t i = 0; i < fmin(num_threads, vctr.size()); ++i) {
        finish += (residue > 0) ? (interval + !!(residue--)) : interval;
        res.push_back(std::vector<int>(vctr.begin() + start, vctr.begin() + finish));
        start = finish;
    }
    return res;
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

std::vector <int> shell_sort(const std::vector <int>& v) {
    int size_n = v.size();
    if (size_n < 1) {
        throw "Wrong size";
    }
    int iter = 0;
    int i = 0;
    int j = 0;
    int tmp = 0;
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

std::vector <int> lin_shell_sort(std::vector<int> vctr, int size) {
    if (size < 1) {
        throw "Wrong size";
    }
    if (size == 1) {
        return vctr;
    }
    std::vector<int> res = vctr;
    std::vector<int> vctr_l;
    std::vector<int> vctr_r;
    if (size % 2 == 0) {
        vctr_l.resize(size / 2);
        vctr_r.resize(size / 2);
    } else {
        vctr_l.resize(size / 2);
        vctr_r.resize(size / 2 + 1);
    }
    std::copy(res.begin(), res.begin() + size / 2, vctr_l.begin());
    std::copy(res.begin() + size / 2, res.end(), vctr_r.begin());
    vctr_l = shell_sort(vctr_l);
    vctr_r = shell_sort(vctr_r);
    res = merge_two_vector(vctr_l, vctr_r);
    return res;
}

std::vector <int> parallel_shell_sort(std::vector<int> vctr, std::size_t num_threads) {
    std::size_t size = vctr.size();
    if (size == 1) {
        return vctr;
    }
    if (size < 1) {
        throw "Wrong size. It should be greater than 0.";
    }
    std::vector<std::vector<int>> splited = partition(vctr, num_threads);
    std::vector<std::thread> thrds;
    std::vector<int> res;
    for (std::size_t i = 0; i < num_threads; i++) {
        thrds.push_back(std::thread([&splited, i]() {
            splited[i] = shell_sort(splited[i]);
            }));
    }
    for (auto& t : thrds) {
        t.join();
    }
    res = splited[0];
    for (std::size_t i = 1; i < num_threads; i++) {
        res = merge_two_vector(res, splited[i]);
    }

    return res;
}
