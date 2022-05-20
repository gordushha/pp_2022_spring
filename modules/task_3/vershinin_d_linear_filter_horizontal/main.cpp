// Copyright 2022 Vershinin Daniil
#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include <tbb/tbb.h>

#include <iostream>
#include <vector>

#include "./linear_filter_horizontal.h"


TEST(TBB_TEST, TestGetParallelOperations_3x3) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 3;
  int height = 3;
  std::vector<float> img = getRandomImage(width, height);

  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);

  std::vector<float> res = getSequentialOperations(width, height, kernel, img);

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

TEST(TBB_TEST, TestGetParallelOperations_128x128) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 128;
  int height = 128;
  std::vector<float> img = getRandomImage(width, height);

  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);

  std::vector<float> res = getSequentialOperations(width, height, kernel, img);

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

TEST(TBB_TEST, TestGetParallelOperations_256x256) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 256;
  int height = 256;
  std::vector<float> img = getRandomImage(width, height);

  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);

  std::vector<float> res = getSequentialOperations(width, height, kernel, img);

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

TEST(TBB_TEST, DISABLED_TestGetParallelOperations_512x512) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 512;
  int height = 512;
  std::vector<float> img = getRandomImage(width, height);

  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);

  std::vector<float> res = getSequentialOperations(width, height, kernel, img);

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

TEST(TBB_TEST, DISABLED_TestGetParallelOperations_1024x1024) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 1024;
  int height = 1024;
  std::vector<float> img = getRandomImage(width, height);

  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);

  std::vector<float> res = getSequentialOperations(width, height, kernel, img);

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

TEST(TBB_TEST, DISABLED_TestGetParallelOperations_1920x1080) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 1920;
  int height = 1080;
  std::vector<float> img = getRandomImage(width, height);

  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);

  std::vector<float> res = getSequentialOperations(width, height, kernel, img);

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

// Test with time

/*
TEST(TBB_TEST, TestGetParallelOperations_3x3) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 3;
  int height = 3;
  std::vector<float> img = getRandomImage(width, height);

  tbb::tick_count t1_start = tbb::tick_count::now();
  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);
  tbb::tick_count t1_finish = tbb::tick_count::now();

  tbb::tick_count t2_start = tbb::tick_count::now();
  std::vector<float> res = getSequentialOperations(width, height, kernel, img);
  tbb::tick_count t2_finish = tbb::tick_count::now();

  double t1 = (t1_finish - t1_start).seconds();
  double t2 = (t2_finish - t2_start).seconds();

  std::cout << "paralel (t1): " << t1 << " seq (t2): " << t2
            << " t2/t1 :" << t2 / t1 << std::endl;

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

TEST(TBB_TEST, TestGetParallelOperations_128x128) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 128;
  int height = 128;
  std::vector<float> img = getRandomImage(width, height);

  tbb::tick_count t1_start = tbb::tick_count::now();
  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);
  tbb::tick_count t1_finish = tbb::tick_count::now();

  tbb::tick_count t2_start = tbb::tick_count::now();
  std::vector<float> res = getSequentialOperations(width, height, kernel, img);
  tbb::tick_count t2_finish = tbb::tick_count::now();

  double t1 = (t1_finish - t1_start).seconds();
  double t2 = (t2_finish - t2_start).seconds();

  std::cout << "paralel (t1): " << t1 << " seq (t2): " << t2
            << " t2/t1 :" << t2 / t1 << std::endl;

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

TEST(TBB_TEST, TestGetParallelOperations_256x256) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 256;
  int height = 256;
  std::vector<float> img = getRandomImage(width, height);

  tbb::tick_count t1_start = tbb::tick_count::now();
  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);
  tbb::tick_count t1_finish = tbb::tick_count::now();

  tbb::tick_count t2_start = tbb::tick_count::now();
  std::vector<float> res = getSequentialOperations(width, height, kernel, img);
  tbb::tick_count t2_finish = tbb::tick_count::now();

  double t1 = (t1_finish - t1_start).seconds();
  double t2 = (t2_finish - t2_start).seconds();

  std::cout << "paralel (t1): " << t1 << " seq (t2): " << t2
            << " t2/t1 :" << t2 / t1 << std::endl;

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

TEST(TBB_TEST, TestGetParallelOperations_512x512) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 512;
  int height = 512;
  std::vector<float> img = getRandomImage(width, height);

  tbb::tick_count t1_start = tbb::tick_count::now();
  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);
  tbb::tick_count t1_finish = tbb::tick_count::now();

  tbb::tick_count t2_start = tbb::tick_count::now();
  std::vector<float> res = getSequentialOperations(width, height, kernel, img);
  tbb::tick_count t2_finish = tbb::tick_count::now();

  double t1 = (t1_finish - t1_start).seconds();
  double t2 = (t2_finish - t2_start).seconds();

  std::cout << "paralel (t1): " << t1 << " seq (t2): " << t2
            << " t2/t1 :" << t2 / t1 << std::endl;

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

TEST(TBB_TEST, TestGetParallelOperations_1024x1024) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 1024;
  int height = 1024;
  std::vector<float> img = getRandomImage(width, height);

  tbb::tick_count t1_start = tbb::tick_count::now();
  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);
  tbb::tick_count t1_finish = tbb::tick_count::now();

  tbb::tick_count t2_start = tbb::tick_count::now();
  std::vector<float> res = getSequentialOperations(width, height, kernel, img);
  tbb::tick_count t2_finish = tbb::tick_count::now();

  double t1 = (t1_finish - t1_start).seconds();
  double t2 = (t2_finish - t2_start).seconds();

  std::cout << "paralel (t1): " << t1 << " seq (t2): " << t2
            << " t2/t1 :" << t2 / t1 << std::endl;

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}

TEST(TBB_TEST, TestGetParallelOperations_1920x1080) {
  std::vector<float> kernel = getGaussKernel(1, 1.5);
  int width = 1920;
  int height = 1080;
  std::vector<float> img = getRandomImage(width, height);

  tbb::tick_count t1_start = tbb::tick_count::now();
  std::vector<float> res_check =
      getParallelOperations(width, height, kernel, img);
  tbb::tick_count t1_finish = tbb::tick_count::now();

  tbb::tick_count t2_start = tbb::tick_count::now();
  std::vector<float> res = getSequentialOperations(width, height, kernel, img);
  tbb::tick_count t2_finish = tbb::tick_count::now();

  double t1 = (t1_finish - t1_start).seconds();
  double t2 = (t2_finish - t2_start).seconds();

  std::cout << "paralel (t1): " << t1 << " seq (t2): " << t2
            << " t2/t1 :" << t2 / t1 << std::endl;

  for (int i = 0; i < width * height; i++) {
    ASSERT_NEAR(res[i], res_check[i], 0.001);
  }
}
*/
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
