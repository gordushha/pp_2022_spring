// Copyright 2022 Shabunin Vladislav
#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "../../3rdparty/unapproved/unapproved.h"
#include "../../modules/task_3/shabunin_v_csr_mult_double/csr_mult_double.h"

using time_interval = std::chrono::duration<long double, std::milli>;
using precise_clock = std::chrono::high_resolution_clock;

template <class Matrix>
time_interval MeasureMulTimeBox(const Matrix lhs, const Matrix rhs, size_t num_threads = 1,
                                size_t num_loops = 15, float box_size = 0.1) {
  std::vector<time_interval> times;
  times.reserve(num_loops);
  for (size_t i = 0; i < num_loops; ++i) {
    Matrix lhs_tmp = lhs, rhs_tmp = rhs;
    lhs_tmp.SetNumThreads(num_threads);
    auto start = precise_clock::now();
    lhs_tmp *= rhs_tmp;
    auto end = precise_clock::now();
    times.emplace_back(end - start);
  }
  std::sort(times.begin(), times.end());
  auto num_entries_to_cut = static_cast<size_t>(static_cast<float>(num_loops) * box_size);
  if (2 * num_entries_to_cut >= num_loops) {
    return time_interval{0};
  }
  size_t res_entries = num_loops - 2 * num_entries_to_cut;
  time_interval sum_time{0};
  for (size_t i = num_entries_to_cut; i + num_entries_to_cut < num_loops; ++i) {
    sum_time += times[i];
  }
  return sum_time / res_entries;
}

TEST(TBB, TestMultEmpty) {
  CSRMatrixTBB<double> l_dmat(2, 5), r_dmat(5, 10);
  l_dmat *= r_dmat;
  CSRMatrixTBB<double> res_dmat(2, 10);
  ASSERT_TRUE(l_dmat == res_dmat);
}

TEST(TBB, TestMultDiag) {
  std::vector<double> diag_mat(10 * 10);
  for (size_t i = 0; i < 10; ++i) {
    diag_mat[i * 10 + i] = 1;
  }
  CSRMatrixTBB<double> l_dmat(10, 10, diag_mat), r_dmat(10, 10, diag_mat);
  l_dmat *= r_dmat;
  CSRMatrixTBB<double> res_dmat(10, 10, diag_mat);
  ASSERT_TRUE(l_dmat == res_dmat);
}

TEST(TBB, TestMultSimpleToDiag) {
  std::vector<double> diag_mat(10 * 10), init_mat(10 * 10);
  for (size_t i = 0; i < 10; ++i) {
    diag_mat[i * 10 + i] = 1;
    for (size_t j = 0; j < 10; ++j) {
      init_mat[i * 10 + j] = RandomDouble::Next();
    }
  }
  CSRMatrixTBB<double> l_dmat(10, 10, init_mat), r_dmat(10, 10, diag_mat);
  l_dmat *= r_dmat;
  CSRMatrixTBB<double> res_dmat(10, 10, init_mat);
  ASSERT_TRUE(l_dmat == res_dmat);
}

TEST(TBB, TestMultDense) {
  size_t same = 32;
  size_t a = same, b = same, c = same;
  std::vector<double> l_init_mat(a * b), r_init_mat(b * c);
  for (size_t i = 0; i < a; ++i) {
    for (size_t j = 0; j < b; ++j) {
      l_init_mat[i * b + j] = RandomDouble::Next();
    }
  }
  for (size_t j = 0; j < b; ++j) {
    for (size_t k = 0; k < c; ++k) {
      r_init_mat[j * c + k] = RandomDouble::Next();
    }
  }
  std::vector<double> res_mat(a * c);
  for (size_t i = 0; i < a; ++i)
    for (size_t j = 0; j < b; ++j)
      for (size_t k = 0; k < c; ++k) {
        res_mat[i * c + k] += l_init_mat[i * b + j] * r_init_mat[j * c + k];
      }
  CSRMatrixTBB<double> l_dmat(a, b, l_init_mat), r_dmat(b, c, r_init_mat);
  time_interval t1 = MeasureMulTimeBox(l_dmat, r_dmat, 1);
  time_interval t2 = MeasureMulTimeBox(l_dmat, r_dmat, 2);
  time_interval t4 = MeasureMulTimeBox(l_dmat, r_dmat, 4);
  time_interval t8 = MeasureMulTimeBox(l_dmat, r_dmat, 8);
  time_interval t16 = MeasureMulTimeBox(l_dmat, r_dmat, 16);
  std::cout.precision(3);
  std::cout << "Threads:\t1\t2\t4\t8\t16\n";
  std::cout << std::fixed << "Times:\t\t" << t1.count() << '\t' << t2.count() << '\t' << t4.count()
            << '\t' << t8.count() << '\t' << t16.count() << '\n';
  std::cout << std::fixed << "Speed up:\t" << 1. << '\t' << t1 / t2 << '\t' << t1 / t4 << '\t'
            << t1 / t8 << '\t' << t1 / t16 << '\n';
  l_dmat *= r_dmat;
  CSRMatrixTBB<double> res_dmat(a, c, res_mat);
  ASSERT_TRUE(l_dmat == res_dmat);
}

TEST(TBB, TestMultSparse) {
  size_t same = 64;
  double zero_per_elem = 2;
  size_t a = same, b = same, c = same;
  std::random_device device;
  std::mt19937 gen(device());
  std::bernoulli_distribution dist(1. / (zero_per_elem + 1.));
  std::vector<double> l_init_mat(a * b), r_init_mat(b * c);
  for (size_t i = 0; i < a; ++i) {
    for (size_t j = 0; j < b; ++j) {
      l_init_mat[i * b + j] = (dist(gen) ? RandomDouble::Next() : 0);
    }
  }
  for (size_t j = 0; j < b; ++j) {
    for (size_t k = 0; k < c; ++k) {
      r_init_mat[j * c + k] = (dist(gen) ? RandomDouble::Next() : 0);
    }
  }
  std::vector<double> res_mat(a * c);
  for (size_t i = 0; i < a; ++i)
    for (size_t j = 0; j < b; ++j)
      for (size_t k = 0; k < c; ++k) {
        res_mat[i * c + k] += l_init_mat[i * b + j] * r_init_mat[j * c + k];
      }
  CSRMatrixTBB<double> l_dmat(a, b, l_init_mat), r_dmat(b, c, r_init_mat);
  time_interval t1 = MeasureMulTimeBox(l_dmat, r_dmat, 1);
  time_interval t2 = MeasureMulTimeBox(l_dmat, r_dmat, 2);
  time_interval t4 = MeasureMulTimeBox(l_dmat, r_dmat, 4);
  time_interval t8 = MeasureMulTimeBox(l_dmat, r_dmat, 8);
  time_interval t16 = MeasureMulTimeBox(l_dmat, r_dmat, 16);
  std::cout.precision(3);
  std::cout << "Threads:\t1\t2\t4\t8\t16\n";
  std::cout << std::fixed << "Times:\t\t" << t1.count() << '\t' << t2.count() << '\t' << t4.count()
            << '\t' << t8.count() << '\t' << t16.count() << '\n';
  std::cout << std::fixed << "Speed up:\t" << 1. << '\t' << t1 / t2 << '\t' << t1 / t4 << '\t'
            << t1 / t8 << '\t' << t1 / t16 << '\n';
  l_dmat *= r_dmat;
  CSRMatrixTBB<double> res_dmat(a, c, res_mat);
  ASSERT_TRUE(l_dmat == res_dmat);
}
