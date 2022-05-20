// Copyright 2022 Nikita Rodionov
#ifndef MODULES_TASK_2_RODIONOV_N_LINKED_AREAS_LOOKUP_OMP_LINKED_AREAS_H_
#define MODULES_TASK_2_RODIONOV_N_LINKED_AREAS_LOOKUP_OMP_LINKED_AREAS_H_
#include <algorithm>
#include <cstdlib>
#include <vector>

struct Equivalents {
  std::vector<std::vector<int>> equivalents;
  void Add(int a, int b) {
    if (a == b) {
      return;
    }
    std::vector<std::vector<int>>::iterator containing = std::find_if(
        equivalents.begin(), equivalents.end(), [&](std::vector<int> p) {
          return std::find_if(p.begin(), p.end(), [&](int p1) {
                   return p1 == a || p1 == b;
                 }) != p.end();
        });
    // We have not found any equivalents
    if (containing == equivalents.end()) {
      std::vector<int> toAdd;
      toAdd.push_back(a);
      toAdd.push_back(b);
      equivalents.push_back(toAdd);
    } else {
      // Contains both
      if (std::find_if(containing->begin(), containing->end(),
                       [&](int p1) { return p1 == a; }) != containing->end() &&
          std::find_if(containing->begin(), containing->end(),
                       [&](int p1) { return p1 == b; }) != containing->end()) {
        // Do nothing
      } else if (std::find_if(containing->begin(), containing->end(),
                              [&](int p1) { return p1 == a; }) !=
                 containing->end()) {
        // Contains first
        containing->push_back(b);

      } else {
        // Contains second
        containing->push_back(a);
      }
    }
  }
  int Get(int a) {
    std::vector<std::vector<int>>::iterator containing = std::find_if(
        equivalents.begin(), equivalents.end(), [&](std::vector<int> p) {
          return std::find_if(p.begin(), p.end(),
                              [&](int p1) { return p1 == a; }) != p.end();
        });
    if (containing == equivalents.end()) {
      return a;
    }
    return *std::min(containing->begin(), containing->end());
  }
};

struct BinaryImage {
  bool** image;
  int size;

  BinaryImage(bool** image, int size) {
    this->image = image;
    this->size = size;
  }

  bool Get(int a, int b) {
    if (a < 0 || b < 0 || a >= size || b >= size) {
      return false;
    }
    return image[a][b];
  }
};

struct BinaryImageAreas {
  int components;
  int** image;
  int size;
  int Get(int a, int b) {
    if (a < 0 || b < 0 || a >= size || b >= size) {
      return -1;
    }
    return image[a][b];
  }
};

BinaryImage GenerateBinrayImage(int size);

BinaryImageAreas* FindAreas(BinaryImage image);

BinaryImageAreas* FindAreasOmp(BinaryImage image);

#endif  // MODULES_TASK_2_RODIONOV_N_LINKED_AREAS_LOOKUP_OMP_LINKED_AREAS_H_
