// Copyright 2022 Preobrazhenskaya Yuliya
#include <gtest/gtest.h>
#include "./histogram_stretching.h"

TEST(STD_Histogram_Stretching, Image_is_empty) {
    int height = 0;
    int width = 0;
    ASSERT_ANY_THROW(getRandomImage(height, width));
}

TEST(STD_Histogram_Stretching, Image_5x5) {
    int height = 5;
    int width = 5;
    std::vector<int> image = getRandomImage(height, width);
    int y_max = getYmax(image, height, width);
    int y_min = getYmin(image, height, width);
    std::vector<int> result_image_seq(height, width);
    std::vector<int> result_image_std(height, width);
    result_image_seq = getSequentialOperations(image, height, width,
        y_max, y_min);
    result_image_std = getParallelOperationsSTD(image, height, width,
        y_max, y_min);
    for (int i = 0; i < height * width; i++) {
        ASSERT_EQ(result_image_seq[i], result_image_std[i]);
    }
}

TEST(STD_Histogram_Stretching, Image_7x10) {
    int height = 7;
    int width = 10;
    std::vector<int> image = getRandomImage(height, width);
    int y_max = getYmax(image, height, width);
    int y_min = getYmin(image, height, width);
    std::vector<int> result_image_seq(height, width);
    std::vector<int> result_image_std(height, width);
    result_image_seq = getSequentialOperations(image, height, width,
        y_max, y_min);
    result_image_std = getParallelOperationsSTD(image, height, width,
        y_max, y_min);
    for (int i = 0; i < height * width; i++) {
        ASSERT_EQ(result_image_seq[i], result_image_std[i]);
    }
}

TEST(STD_Histogram_Stretching, Image_10x15) {
    int height = 10;
    int width = 15;
    std::vector<int> image = getRandomImage(height, width);
    int y_max = getYmax(image, height, width);
    int y_min = getYmin(image, height, width);
    std::vector<int> result_image_seq(height, width);
    std::vector<int> result_image_std(height, width);
    result_image_seq = getSequentialOperations(image, height, width,
        y_max, y_min);
    result_image_std = getParallelOperationsSTD(image, height, width,
        y_max, y_min);
    for (int i = 0; i < height * width; i++) {
        ASSERT_EQ(result_image_seq[i], result_image_std[i]);
    }
}

TEST(STD_Histogram_Stretching, Image_40x20) {
    int height = 40;
    int width = 20;
    std::vector<int> image = getRandomImage(height, width);
    int y_max = getYmax(image, height, width);
    int y_min = getYmin(image, height, width);
    std::vector<int> result_image_seq(height, width);
    std::vector<int> result_image_std(height, width);
    result_image_seq = getSequentialOperations(image, height, width,
        y_max, y_min);
    result_image_std = getParallelOperationsSTD(image, height, width,
        y_max, y_min);
    for (int i = 0; i < height * width; i++) {
        ASSERT_EQ(result_image_seq[i], result_image_std[i]);
    }
}

TEST(STD_Histogram_Stretching, Image_50x50) {
    int height = 50;
    int width = 50;
    std::vector<int> image = getRandomImage(height, width);
    int y_max = getYmax(image, height, width);
    int y_min = getYmin(image, height, width);
    std::vector<int> result_image_seq(height, width);
    std::vector<int> result_image_std(height, width);
    result_image_seq = getSequentialOperations(image, height, width,
        y_max, y_min);
    result_image_std = getParallelOperationsSTD(image, height, width,
        y_max, y_min);
    for (int i = 0; i < height * width; i++) {
        ASSERT_EQ(result_image_seq[i], result_image_std[i]);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
