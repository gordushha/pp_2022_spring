// Copyright 2022 Nikita Rodionov
#include <gtest/gtest.h>
#include <cstdio>
#include <iostream>
#include <gtest-mpi-listener.hpp>
#include "../../../modules/task_1/rodionov_n_linked_areas_lookup/linked_areas.h"


const int IMAGE_SIZE1 = 10;
const int IMAGE_SIZE2 = 50;
const int IMAGE_SIZE3 = 100;

TEST(LinkedAreasLookup, GenerateBinaryImageTest1) {
    BinaryImage image = GenerateBinrayImage(IMAGE_SIZE1);

    ASSERT_EQ(image.size, IMAGE_SIZE1);
}
TEST(LinkedAreasLookup, FindAreasTest1) {
    BinaryImage image = GenerateBinrayImage(IMAGE_SIZE1);
    FindAreas(image);
}

TEST(LinkedAreasLookup, GenerateBinaryImageTest2) {
    BinaryImage image = GenerateBinrayImage(IMAGE_SIZE2);

    ASSERT_EQ(image.size, IMAGE_SIZE2);
}
TEST(LinkedAreasLookup, FindAreasTest2) {
    BinaryImage image = GenerateBinrayImage(IMAGE_SIZE2);
    FindAreas(image);
}

TEST(LinkedAreasLookup, GenerateBinaryImageTest3) {
    BinaryImage image = GenerateBinrayImage(IMAGE_SIZE3);
    ASSERT_EQ(image.size, IMAGE_SIZE3);
}
TEST(LinkedAreasLookup, FindAreasTest3) {
    BinaryImage image = GenerateBinrayImage(IMAGE_SIZE3);
    FindAreas(image);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    return RUN_ALL_TESTS();
}
