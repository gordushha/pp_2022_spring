// Copyright 2022 Nikita Rodionov
#include <gtest/gtest.h>
#include <cstdio>
#include <iostream>
#include <gtest-mpi-listener.hpp>
#include "./linked_areas.h"

const int IMAGE_SIZE1 = 5;
const int IMAGE_SIZE2 = 10;
const int IMAGE_SIZE3 = 20;
const int IMAGE_SIZE4 = 50;
const int IMAGE_SIZE5 = 100;


bool CompareAreas(BinaryImageAreas* area1, BinaryImageAreas* area2) {
  if (area1->size != area2->size) {
    return false;
  }
  for (int x = 0; x < area1->size; x++) {
    for (int y = 0; y < area1->size; y++) {
      int a = area1->Get(x, y);
      int b = area2->Get(x, y);
      if ((a == -1) != (b == -1)) {
        return false;
      }
    }
  }
  return true;
}


TEST(LinkedAreasLookup, EqualityTest1) {
    BinaryImage image = GenerateBinrayImage(IMAGE_SIZE1);
    BinaryImageAreas* areas = FindAreas(image);
    BinaryImageAreas* areasOmp = FindAreasOmp(image);
    bool valid = CompareAreas(areas, areasOmp);
    ASSERT_TRUE(valid);
}

TEST(LinkedAreasLookup, EqualityTest2) {
  BinaryImage image = GenerateBinrayImage(IMAGE_SIZE2);
  BinaryImageAreas* areas = FindAreas(image);
  BinaryImageAreas* areasOmp = FindAreasOmp(image);
  bool valid = CompareAreas(areas, areasOmp);
  ASSERT_TRUE(valid);
}

TEST(LinkedAreasLookup, EqualityTest3) {
  BinaryImage image = GenerateBinrayImage(IMAGE_SIZE3);
  BinaryImageAreas* areas = FindAreas(image);
  BinaryImageAreas* areasOmp = FindAreasOmp(image);
  bool valid = CompareAreas(areas, areasOmp);
  ASSERT_TRUE(valid);
}

TEST(LinkedAreasLookup, EqualityTest4) {
  BinaryImage image = GenerateBinrayImage(IMAGE_SIZE4);
  BinaryImageAreas* areas = FindAreas(image);
  BinaryImageAreas* areasOmp = FindAreasOmp(image);
  bool valid = CompareAreas(areas, areasOmp);
  ASSERT_TRUE(valid);
}

TEST(LinkedAreasLookup, EqualityTest5) {
  BinaryImage image = GenerateBinrayImage(IMAGE_SIZE5);
  BinaryImageAreas* areas = FindAreas(image);
  BinaryImageAreas* areasOmp = FindAreasOmp(image);
  bool valid = CompareAreas(areas, areasOmp);
  ASSERT_TRUE(valid);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    return RUN_ALL_TESTS();
}
