// Copyright 2022 Ershov Aleksey
#include <gtest/gtest.h>

// #include <chrono>
// #include <iostream>
#include <vector>

#include "./deicstra_std.h"

TEST(Sequential_Deicstra, Test_Get_Deicstra_With_Static_Data_No_Throw) {
  const std::vector<std::vector<int>> graf = {
      {0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0}, {9, 10, 0, 11, 0, 2},
      {0, 15, 11, 0, 6, 0}, {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};

  ASSERT_NO_THROW(getDeicstra(graf, 0));
}

TEST(Sequential_Deicstra, Test_Sequential_Deicstra_With_Static_Data_No_Throw) {
  const std::vector<std::vector<int>> graf = {
      {0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0}, {9, 10, 0, 11, 0, 2},
      {0, 15, 11, 0, 6, 0}, {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};

  ASSERT_NO_THROW(getSequentialDeicstra(graf));
}

TEST(Parallel_Deicstra, Test_Parallel_Deicstra_With_Static_Data_No_Throw) {
  const std::vector<std::vector<int>> graf = {
      {0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0}, {9, 10, 0, 11, 0, 2},
      {0, 15, 11, 0, 6, 0}, {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};

  ASSERT_NO_THROW(getParallelDeicstra(graf));
}

TEST(Sequential_Deicstra, Test_Sequential_Deicstra_With_Static_Data) {
  const std::vector<std::vector<int>> graf = {
      {0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0}, {9, 10, 0, 11, 0, 2},
      {0, 15, 11, 0, 6, 0}, {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};
  const std::vector<int> trueResult = {
      0,  7,  9,  20, 20, 11, 7,  0,  10, 15, 21, 12, 9,  10, 0, 11, 11, 2,
      20, 15, 11, 0,  6,  13, 20, 21, 11, 6,  0,  9,  11, 12, 2, 13, 9,  0};
  bool check = true;
  const int count = graf.size();

  const std::vector<int> algorithmResult = getSequentialDeicstra(graf);
  for (int i = 0; i < count; ++i) {
    if (trueResult[i] != algorithmResult[i]) {
      check = false;
    }
  }

  ASSERT_EQ(check, true);
}

TEST(Sequential_Deicstra, Test_Sequential_Deicstra_Two_Times_Static) {
  const std::vector<std::vector<int>> graf = {
      {0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0}, {9, 10, 0, 11, 0, 2},
      {0, 15, 11, 0, 6, 0}, {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};
  bool check = true;
  const int count = graf.size();

  const std::vector<int> algorithmResultFirst = getSequentialDeicstra(graf);

  const std::vector<int> algorithmResultSecond = getSequentialDeicstra(graf);

  for (int i = 0; i < count; ++i) {
    if (algorithmResultFirst[i] != algorithmResultSecond[i]) {
      check = false;
    }
  }

  ASSERT_EQ(check, true);
}

TEST(Sequential_Deicstra, Test_Sequential_Deicstra_Two_Times_Random) {
  const std::vector<std::vector<int>> graf = getRandomVector(10);
  bool check = true;
  const int count = graf.size();

  const std::vector<int> algorithmResultFirst = getSequentialDeicstra(graf);

  const std::vector<int> algorithmResultSecond = getSequentialDeicstra(graf);

  for (int i = 0; i < count; ++i) {
    if (algorithmResultFirst[i] != algorithmResultSecond[i]) {
      check = false;
    }
  }

  ASSERT_EQ(check, true);
}

TEST(Parallel_Deicstra, Test_Parallel_Deicstra_With_Seq_Static) {
  const std::vector<std::vector<int>> graf = {
      {0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0}, {9, 10, 0, 11, 0, 2},
      {0, 15, 11, 0, 6, 0}, {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};
  bool check = true;
  const int count = graf.size();

  const std::vector<int> algorithmResultSeq = getSequentialDeicstra(graf);

  const std::vector<int> algorithmResultRarallel = getParallelDeicstra(graf);

  for (int i = 0; i < count; ++i) {
    if (algorithmResultSeq[i] != algorithmResultRarallel[i]) {
      check = false;
    }
  }

  ASSERT_EQ(check, true);
}

TEST(Parallel_Deicstra, Test_Parallel_Deicstra_With_Seq_Random) {
  const std::vector<std::vector<int>> graf = getRandomVector(250);
  bool check = true;
  const int count = graf.size();

  // auto t1 = std::chrono::system_clock::now();
  const std::vector<int> algorithmResultSeq = getSequentialDeicstra(graf);
  // auto t2 = std::chrono::system_clock::now();
  // auto dt = t2 - t1;
  // std::cout << "Sequential time = " << dt.count() << std::endl;

  // t1 = std::chrono::system_clock::now();
  const std::vector<int> algorithmResultRarallel = getParallelDeicstra(graf);
  // t2 = std::chrono::system_clock::now();
  // dt = t2 - t1;
  // std::cout << "Parallel time = " << dt.count() << std::endl;

  for (int i = 0; i < count; ++i) {
    if (algorithmResultSeq[i] != algorithmResultRarallel[i]) {
      check = false;
    }
  }

  ASSERT_EQ(check, true);
}
