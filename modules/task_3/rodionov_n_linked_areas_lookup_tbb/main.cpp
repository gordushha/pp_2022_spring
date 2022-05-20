// Copyright 2022 Nikita Rodionov
#include <gtest/gtest.h>
#include <iostream>
#include <cstdio>
#include "./linked_areas.h"

const int IMAGE_SIZE1 = 5;
const int IMAGE_SIZE2 = 10;
const int IMAGE_SIZE3 = 20;
const int IMAGE_SIZE4 = 30;
const int IMAGE_SIZE5 = 50;

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
  BinaryImageAreas* areasOmp = FindAreasTBB(image);
  /*
      for (int x = 0; x < image.size; x++) {
    std::cout << "\n";
    for (int y = 0; y < image.size; y++) {
      std::cout << image.Get(x, y) << " ";
    }
  }
  std::cout << "\n";
  std::cout << "\n";
  for (int x=0;x<image.size;x++) {
    std::cout << "\n";
    for (int y = 0; y < image.size; y++) {
      std::cout << areas->Get(x, y) << " ";
    }
  }
  std::cout << "\n";
  std::cout << "\n";
  for (int x = 0; x < image.size; x++) {
    std::cout << "\n";
    for (int y = 0; y < image.size; y++) {
      std::cout << areasOmp->Get(x, y) << " ";
    }
  }
  */
  bool valid = CompareAreas(areas, areasOmp);
  ASSERT_TRUE(valid);
}

TEST(LinkedAreasLookup, EqualityTest2) {
  BinaryImage image = GenerateBinrayImage(IMAGE_SIZE2);
  BinaryImageAreas* areas = FindAreas(image);
  BinaryImageAreas* areasOmp = FindAreasTBB(image);
  bool valid = CompareAreas(areas, areasOmp);
  ASSERT_TRUE(valid);
}

TEST(LinkedAreasLookup, EqualityTest3) {
  BinaryImage image = GenerateBinrayImage(IMAGE_SIZE3);
  BinaryImageAreas* areas = FindAreas(image);
  BinaryImageAreas* areasOmp = FindAreasTBB(image);
  bool valid = CompareAreas(areas, areasOmp);
  ASSERT_TRUE(valid);
}

TEST(LinkedAreasLookup, EqualityTest4) {
  BinaryImage image = GenerateBinrayImage(IMAGE_SIZE4);
  BinaryImageAreas* areas = FindAreas(image);
  BinaryImageAreas* areasOmp = FindAreasTBB(image);
  bool valid = CompareAreas(areas, areasOmp);
  ASSERT_TRUE(valid);
}

TEST(LinkedAreasLookup, EqualityTest5) {
  BinaryImage image = GenerateBinrayImage(IMAGE_SIZE5);
  BinaryImageAreas* areas = FindAreas(image);
  BinaryImageAreas* areasOmp = FindAreasTBB(image);
  bool valid = CompareAreas(areas, areasOmp);
  ASSERT_TRUE(valid);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
