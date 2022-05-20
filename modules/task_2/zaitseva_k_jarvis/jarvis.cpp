// Copyright 2022 Zaitseva Ksenia
#include "../../modules/task_2/zaitseva_k_jarvis/jarvis.h"

bool Point::operator<(const Point& other) const {
  if ((y < other.y) || ((y == other.y) && (x > other.x)))
    return 1;
  else
    return 0;
}

bool Point::operator==(const Point& other) const {
  return (std::fabs(x - other.x) <
          1000 * std::numeric_limits<double>::epsilon()) &&
         (std::fabs(y - other.y) <
          1000 * std::numeric_limits<double>::epsilon());
}

bool Point::operator!=(const Point& other) const { return !(*this == other); }

Point Point::operator-(const Point& other) const {
  return Point(x - other.x, y - other.y);
}

double cross(const Point& a, const Point& b) { return a.x * b.y - b.x * a.y; }

bool turn(const Point& a, const Point& b, const Point& c) {
  double det = cross(b - a, c - a);
  if (det > 0.0) {
    return 0;
  } else if (det < 0.0) {
    return 1;
  } else if (det == 0.0) {
    double distans_a_b =
        std::sqrt((b.x - a.x) * (b.x - a.x) * (b.y - a.y) * (b.y - a.y));
    double distans_a_c =
        std::sqrt((c.x - a.x) * (c.x - a.x) * (c.y - a.y) * (c.y - a.y));
    if (distans_a_c > distans_a_b)
      return 1;
    else
      return 0;
  }
  return 0;
}

std::vector<Point> Jarvis(std::vector<Point> points) {
  Point p0 = points[0];
  int k = 0;
  for (std::size_t i = 1; i < points.size(); i++) {
    if (points[i] < p0) {
      p0 = points[i];
      k = i;
    }
  }
  std::swap(points[k], points[0]);
  Point p_next, p_i = p0;
  std::size_t i = 1;
  for (i = 1; i < points.size(); i++) {
    p_next = points[i];
    k = i;
    for (std::size_t j = i + 1; j < points.size(); j++) {
      if (turn(p_i, p_next, points[j])) {
        p_next = points[j];
        k = j;
      }
    }
    if (turn(p_i, p_next, p0)) {
      break;
    }
    std::swap(points[k], points[i]);
    p_i = p_next;
  }
  return std::vector<Point>(points.begin(), points.begin() + i);
}

std::vector<Point> Generate(int n) {
  std::vector<Point> res;
  std::default_random_engine engine;
  std::uniform_real_distribution<double> uniform(-10, 10);
  for (int i = 0; i < n; i++) {
    res.push_back(Point(uniform(engine), uniform(engine)));
  }
  return res;
}

std::vector<Point> Jarvis_parallel(std::vector<Point> points) {
  int num_threads = 2;
  omp_set_num_threads(num_threads);
  std::vector<Point> mins(num_threads);
  std::vector<int> mins_k(num_threads);
  int n = points.size();
#pragma omp parallel
  {
    int th_num = omp_get_thread_num();
    mins[th_num] = points[0];
    mins_k[th_num] = 0;
#pragma omp for
    for (int i = 1; i < n; i++) {
      if (points[i] < mins[th_num]) {
        mins[th_num] = points[i];
        mins_k[th_num] = i;
      }
    }
  }
  Point p0 = mins[0];
  int k = mins_k[0];
  for (int i = 1; i < num_threads; i++) {
    if (mins[i] < p0) {
      p0 = mins[i];
      k = mins_k[i];
    }
  }
  std::swap(points[k], points[0]);
  Point p_next, p_i = p0;
  int i = 1;
  for (i = 1; i < n; i++) {
    p_next = points[i];
    k = i;
    for (std::size_t j = i + 1; j < points.size(); j++) {
      if (turn(p_i, p_next, points[j])) {
        p_next = points[j];
        k = j;
      }
    }
    if (turn(p_i, p_next, p0)) {
      break;
    }
    std::swap(points[k], points[i]);
    p_i = p_next;
  }
  return std::vector<Point>(points.begin(), points.begin() + i);
}
