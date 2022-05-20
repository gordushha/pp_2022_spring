// Copyright 2022 Nikita Rodionov
#include "../../../modules/task_1/rodionov_n_linked_areas_lookup/linked_areas.h"

#include <map>
#include <random>
#include <vector>
#include <algorithm>
// #include <opencv2/core.hpp>
// #include <opencv2/imgcodecs.hpp>
// #include <opencv2/highgui.hpp>

BinaryImage GenerateBinrayImage(int size) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1);

  auto image = BinaryImage(size);
  for (int x = 0; x < size; x++) {
    image.image[x] = new bool[size];
    for (int y = 0; y < size; y++) {
      image.image[x][y] = dist(rng);
    }
  }
  return image;
}

/*
void show(BinaryImageAreas image) {
    cv::Mat img = cv::Mat(image.size, image.size, CV_8U);

    for (int i = 0; i < image.size * image.size; i++) {
        int x = i / image.size;
        int y = i % image.size;

        unsigned char& color = img.at<unsigned char>(y, x);
        unsigned char colors[2] = { 100, 255 };
        if (image.Get(x, y) == -1) {
            color = 0;
        } else {
            color = colors[image.Get(x, y) % 2];
        }
    }
    cv::imshow("Display window", img);

    cv::waitKey();
}
*/

BinaryImageAreas* FindAreas(BinaryImage image) {
  BinaryImageAreas* areas = new BinaryImageAreas();
  areas->size = image.size;
  areas->image = new int*[image.size];
  for (int x = 0; x < image.size; x++) {
    areas->image[x] = new int[image.size];
    for (int y = 0; y < image.size; y++) {
      areas->image[x][y] = -1;
    }
  }

  std::map<int, std::vector<int>> equivalents;

  int label = -1;
  // First pass
  for (int x = 1; x < image.size; x++)
    for (int y = 1; y < image.size; y++) {
      if (!image.Get(x, y)) {
        continue;
      }

      int _1 = areas->Get(x, y + 1);
      int _2 = areas->Get(x + 1, y);
      int _3 = areas->Get(x, y - 1);
      int _4 = areas->Get(x - 1, y);

      int total_non_bg =
          static_cast<int>(_1 != -1) + static_cast<int>(_2 != -1) +
          static_cast<int>(_3 != -1) + static_cast<int>(_4 != -1);
      if (total_non_bg == 0) {
        areas->image[x][y] = label;
        label++;
      } else if (total_non_bg == 1) {
        if (_1 != -1) {
          areas->image[x][y] = _1;
        }
        if (_2 != -1) {
          areas->image[x][y] = _2;
        }
        if (_3 != -1) {
          areas->image[x][y] = _3;
        }
        if (_4 != -1) {
          areas->image[x][y] = _4;
        }
      } else {
        int nonzero[4];
        int sz = 0;
        if (_1 != -1) {
          nonzero[sz] = _1;
          sz++;
        }
        if (_2 != -1) {
          nonzero[sz] = _2;
          sz++;
        }
        if (_3 != -1) {
          nonzero[sz] = _3;
          sz++;
        }
        if (_4 != -1) {
          nonzero[sz] = _4;
          sz++;
        }
        areas->image[x][y] = nonzero[0];

        for (int i = 0; i < sz; i++) {
          if (nonzero[i] != nonzero[0]) {
            if (equivalents.find(nonzero[0]) != equivalents.end()) {
              if (std::find(equivalents.at(nonzero[0]).begin(),
                            equivalents.at(nonzero[0]).end(),
                            nonzero[i]) == equivalents.at(nonzero[0]).end()) {
                // Not contains
                equivalents.at(nonzero[0]).push_back(nonzero[i]);
              }
            } else if (equivalents.find(nonzero[i]) != equivalents.end()) {
              if (std::find(equivalents.at(nonzero[i]).begin(),
                            equivalents.at(nonzero[i]).end(),
                            nonzero[i]) == equivalents.at(nonzero[i]).end()) {
                // Not contains
                equivalents.at(nonzero[i]).push_back(nonzero[0]);
              }
            } else {
              equivalents.insert(
                  std::make_pair(nonzero[0], std::vector<int>()));
              if (std::find(equivalents.at(nonzero[0]).begin(),
                            equivalents.at(nonzero[0]).end(),
                            nonzero[i]) == equivalents.at(nonzero[0]).end()) {
                // Not contains
                equivalents.at(nonzero[0]).push_back(nonzero[i]);
              }
            }
          }
        }
      }
    }

  // Second pass
  for (int x = 1; x < image.size; x++)
    for (int y = 1; y < image.size; y++) {
      int _00 = areas->Get(x, y);
      if (equivalents.find(_00) != equivalents.end()) {
        auto& vector = equivalents.at(_00);
        _00 = vector.at(0);
      }
    }
  areas->components = label;
  return areas;
}
