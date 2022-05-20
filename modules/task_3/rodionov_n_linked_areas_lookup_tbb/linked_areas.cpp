// Copyright 2022 Nikita Rodionov
#include "../../../modules/task_3/rodionov_n_linked_areas_lookup_tbb/linked_areas.h"
#include <algorithm>
#include <functional>
#include <map>
#include <numeric>
#include <random>
#include <vector>
BinaryImage GenerateBinrayImage(int size) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1);

  bool** image = new bool*[size];
  for (int x = 0; x < size; x++) {
    image[x] = new bool[size];
    for (int y = 0; y < size; y++) {
      image[x][y] = dist(rng);
    }
  }
  return BinaryImage(image, size);
}
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

  Equivalents equivalents;
  int label = 0;
  // First pass
  for (int x = 0; x < image.size; x++)
    for (int y = 0; y < image.size; y++) {
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
        ++label;
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
        int nonzero[4] = {-1};
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
          if (nonzero[i] == -1) {
            continue;
          }
          equivalents.Add(nonzero[0], nonzero[i]);
        }
      }
    }

  // Second pass
  for (int x = 0; x < image.size; x++) {
    for (int y = 0; y < image.size; y++) {
      int _00 = areas->Get(x, y);
      areas->image[x][y] = equivalents.Get(_00);
    }
  }
  areas->components = equivalents.equivalents.size();
  return areas;
}

struct RowProcessor {
  int rows;
  BinaryImage* image;
  BinaryImageAreas* areas;
  Equivalents* equivalents;
  RowProcessor(BinaryImage* image, BinaryImageAreas* areas,
               Equivalents* equivalents, int rows) {
    this->rows = rows;
    this->image = image;
    this->areas = areas;
    this->equivalents = equivalents;
  }
  RowProcessor(const RowProcessor& processor, tbb::split) {
    this->rows = processor.rows;
    this->image = processor.image;
    this->areas = processor.areas;
    this->equivalents = processor.equivalents;
  }
  void operator()(const tbb::blocked_range<int>& r) const {
    for (tbb::blocked_range<int>::const_iterator x = r.begin(); x != r.end(); ++x) {
      int label = x * image->size + 1;
      for (int y = 0; y < this->rows; y++) {
        if (!image->Get(x, y)) {
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
          ++label;
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
          int nonzero[4] = {-1};
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
            if (nonzero[i] == -1) {
              continue;
            }
            equivalents->Add(nonzero[0], nonzero[i]);
          }
        }
      }
    }
  }
  void join(const RowProcessor& rhs) {}
};

BinaryImageAreas* FindAreasTBB(BinaryImage image) {
  BinaryImageAreas* areas = new BinaryImageAreas();
  std::vector<int> columns;
  areas->size = image.size;
  areas->image = new int*[image.size];
  for (int x = 0; x < image.size; x++) {
    columns.push_back(x);
    areas->image[x] = new int[image.size];
    for (int y = 0; y < image.size; y++) {
      areas->image[x][y] = -1;
    }
  }

  Equivalents equivalents;
  tbb::task_scheduler_init init(1);
  RowProcessor processor(&image, areas, &equivalents, image.size);

  tbb::parallel_for(tbb::blocked_range<int>(0, image.size), processor);
  // Second pass
  for (int x = 0; x < image.size; x++) {
    for (int y = 0; y < image.size; y++) {
      int _00 = areas->Get(x, y);
      areas->image[x][y] = equivalents.Get(_00);
    }
  }
  equivalents.equivalents.size();
  return areas;
}
