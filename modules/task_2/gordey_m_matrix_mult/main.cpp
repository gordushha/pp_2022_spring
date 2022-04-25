// Copyright 2022 Gordey Maria
#include <gtest/gtest.h>
#include <omp.h>
#include "../../../modules/task_2/gordey_m_matrix_mult/matrix_mult.h"

TEST(SPARSE_MATRIX_MULT_SEQ, CREATE_MATRIX) {
    double* arr = create_random_matrix(4);
    SparseM A(arr, 2, 2);
    SparseM B(arr, 2, 2);
    ASSERT_EQ(1, 1);
}

TEST(SPARSE_MATRIX_MULT_SEQ, TRANSPOSE) {
    double arr[] = { 1, 0, 0, 2 };
    double arr2[] = { 0, 3, 7, 0 };
    double arr3[] = { 0, 3, 14, 0 };
    SparseM A(arr, 2, 2);
    SparseM B(arr2, 2, 2);
    SparseM C(arr3, 2, 2);
    ASSERT_EQ(1, 1);
}

TEST(SPARSE_MATRIX_MULT_SEQ, MULT_1) {
    double arr[] = { 0, 5, 0, 0, 1, 0, 3, 0, 8 };
    double arr2[] = { 1, 0, 0, 0, 0, 1, 0, 0, 4};
    double arr3[] = { 0, 0, 5, 0, 0, 1, 3, 0, 32};
    SparseM A(arr, 3, 3);
    SparseM B(arr2, 3, 3);
    SparseM C(arr3, 3, 3);
    ASSERT_EQ(C == A * B, true);
}

TEST(SPARSE_MATRIX_MULT_SEQ, MULT_2) {
    int count = 100;
    double* arr = create_random_matrix(count*count);
    double* arr1 = create_random_matrix(count*count);
    SparseM A(arr, count, count);
    SparseM B(arr1, count, count);
    delete[] arr;
    delete[] arr1;
     double start_seq = omp_get_wtime();
    SparseM C = A * B;
     double end_seq = omp_get_wtime();
     double seq_time = end_seq - start_seq;
     double start_omp = omp_get_wtime();
    SparseM D = Mult_parallel(A, B);
     double end_omp = omp_get_wtime();
     double omp_time = end_omp - start_omp;
     std::cout << "seq time: " << seq_time << "\n";
     std::cout << "omp time: " << omp_time << "\n";
     std::cout << "a: " << seq_time / omp_time << "\n";
    ASSERT_EQ(D, C);
}

TEST(SPARSE_MATRIX_MULT_SEQ, MULT_3) {
    int count = 500;
    double* arr = create_random_matrix(count*count);
    double* arr1 = create_random_matrix(count*count);
    SparseM A(arr, count, count);
    SparseM B(arr1, count, count);
    delete[] arr;
    delete[] arr1;
     double start_seq = omp_get_wtime();
    SparseM C = A * B;
    double end_seq = omp_get_wtime();
    double seq_time = end_seq - start_seq;
    double start_omp = omp_get_wtime();
    SparseM D = Mult_parallel(A, B);
    double end_omp = omp_get_wtime();
    double omp_time = end_omp - start_omp;
    std::cout << "seq time: " << seq_time << "\n";
    std::cout << "omp time: " << omp_time << "\n";
    std::cout << "a: " << seq_time / omp_time << "\n";
    ASSERT_EQ(D, C);
}
TEST(SPARSE_MATRIX_MULT_SEQ, MULT_4) {
  int count = 1000;
  double* arr = create_random_matrix(count * count);
  double* arr1 = create_random_matrix(count * count);
  SparseM A(arr, count, count);
  SparseM B(arr1, count, count);
  delete[] arr;
  delete[] arr1;
  double start_seq = omp_get_wtime();
  SparseM C = A * B;
  double end_seq = omp_get_wtime();
  double seq_time = end_seq - start_seq;
  double start_omp = omp_get_wtime();
  SparseM D = Mult_parallel(A, B);
  double end_omp = omp_get_wtime();
  double omp_time = end_omp - start_omp;
  std::cout << "seq time: " << seq_time << "\n";
  std::cout << "omp time: " << omp_time << "\n";
  std::cout << "a: " << seq_time / omp_time << "\n";
  ASSERT_EQ(D, C);
}
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
