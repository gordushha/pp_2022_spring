// Copyright 2022 Preobrazhenskaya Yuliya
#include <random>
#include "../../../3rdparty/unapproved/unapproved.h"
#include "../../../modules/task_4/preobrazhenskaya_y_histogram_stretching/histogram_stretching.h"

std::vector<int> getRandomImage(int height, int width) {
    if (height <= 0 || width <= 0) {
        throw - 1;
    }
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> image(height * width);
    for (int i = 0; i < height * width; i++) { image[i] = gen() % 256; }
    return image;
}

int getYmax(std::vector<int> image, int height, int width) {
    if (height <= 0 || width <= 0) {
        throw - 1;
    }
    int y_max = 0;
    for (int i = 0; i < height * width; i++) {
        if (image[i] > y_max) {
            y_max = image[i];
        }
    }
    return y_max;
}

int getYmin(std::vector<int> image, int height, int width) {
    if (height <= 0 || width <= 0) {
        throw - 1;
    }
    int y_min = 255;
    for (int i = 0; i < height * width; i++) {
        if (image[i] < y_min) {
            y_min = image[i];
        }
    }
    return y_min;
}

std::vector<int> getSequentialOperations(std::vector<int> image,
    int height, int width, int y_max, int y_min) {
    if (height <= 0 || width <= 0) {
        throw - 1;
    }
    std::vector<int> result_image(height * width);
    for (int i = 0; i < height * width; i++) {
        result_image[i] = static_cast<int>
            ((image[i] - y_min) * ((255 - 0) / (y_max - y_min)));
        if (result_image[i] < 0) {
            result_image[i] = 0;
        }
        if (result_image[i] > 255) {
            result_image[i] = 255;
        }
    }
    return result_image;
}

std::vector<int> getParallelOperationsSTD(std::vector<int> image,
    int height, int width, int y_max, int y_min) {
    if (height <= 0 || width <= 0) {
        throw - 1;
    }
    std::vector<int> result_image(height * width);

    const int threads_num = 6;
    int delta = (height * width) / threads_num;
    std::vector<std::thread> threads;
    std::vector<int> parts(threads_num + 1);
    for (int i = 0; i < threads_num; i++) {
        parts[i] = i * delta;
    }
    parts[threads_num] = height * width;
    for (int i = 0; i < threads_num; i++) {
        std::thread t([&](const int i) {
            for (int j = parts[i]; j < parts[i + 1]; j++) {
                result_image[j] =
                    static_cast<int>
                    ((image[j] - y_min) * ((255 - 0) / (y_max - y_min)));
                if (result_image[j] < 0) {
                    result_image[j] = 0;
                }
                if (result_image[j] > 255) {
                    result_image[j] = 255;
                }
            }
        }, i);
        threads.emplace_back(std::move(t));
    }
    for (int i = 0; i < threads_num; i++) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }
    return result_image;
}
