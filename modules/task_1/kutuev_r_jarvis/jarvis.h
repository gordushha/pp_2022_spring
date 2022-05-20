// Copyright 2022 Kutuev Roman
#ifndef MODULES_TASK_1_KUTUEV_R_JARVIS_JARVIS_H_
#define MODULES_TASK_1_KUTUEV_R_JARVIS_JARVIS_H_

#include <omp.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <random>
#include <stack>
#include <vector>

#define collinear 0
#define left -1
#define right 1

struct Point {
  int x;
  int y;
  void set_point(int _x, int _y) {
    x = _x;
    y = _y;
  }
};

class jarvis {
 public:
  std::vector<Point> set_points(int size);

  int find_lowest_left_most_point_index(const std::vector<Point>& points);

  int orientation(const Point& p0, const Point& p1, const Point& p2);

  int sq_distance(const Point& p0, const Point& p1);

  std::vector<Point> convex_hull(const std::vector<Point>& points);
};

#endif  // MODULES_TASK_1_KUTUEV_R_JARVIS_JARVIS_H_
