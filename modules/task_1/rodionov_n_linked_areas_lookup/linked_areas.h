// Copyright 2022 Nikita Rodionov
#ifndef MODULES_TASK_1_RODIONOV_N_LINKED_AREAS_LOOKUP_LINKED_AREAS_H_
#define MODULES_TASK_1_RODIONOV_N_LINKED_AREAS_LOOKUP_LINKED_AREAS_H_

#include <cstdlib>
struct BinaryImage {
    bool** image;
    int size;

    explicit BinaryImage(int size) {
        this->image = new bool*[size];
        for (int i = 0; i < size; i++) {
            this->image[i] = new bool[size];
        }
        this->size = size;
    }
    bool Get(int a, int b) {
        if (a < 0 || b < 0 || a >= size || b >= size) {
            return false;
        }
        return image[a][b];
    }

    ~BinaryImage() {
        for (int i = 0; i < this->size; i++) {
          delete[] this->image[i];
        }
        delete[] this->image;
    }
    BinaryImage(const BinaryImage& image) {
      this->image = new bool*[image.size];
      for (int i = 0; i < image.size; i++) {
        this->image[i] = new bool[image.size];
        for (int j = 0; j < image.size; j++) {
          this->image[i][j] = image.image[i][j];
        }
      }
      this->size = image.size;
    }
    BinaryImage operator= (const BinaryImage& image) {
      this->image = new bool*[image.size];
      for (int i = 0; i < image.size; i++) {
        this->image[i] = new bool[image.size];
        for (int j = 0; j < image.size; j++) {
          this->image[i][j] = image.image[i][j];
        }
      }
      this->size = image.size;
      return *this;
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
    ~BinaryImageAreas() {
      for (int i = 0; i < this->size; i++) {
        delete[] this->image[i];
      }
      delete[] this->image;
    }
};


BinaryImage GenerateBinrayImage(int size);

BinaryImageAreas* FindAreas(BinaryImage image);

void show(BinaryImageAreas image);
#endif  // MODULES_TASK_1_RODIONOV_N_LINKED_AREAS_LOOKUP_LINKED_AREAS_H_
