// Copyright 2022 VODENEEV MIKHAIL

#include <iostream>
#include "../../../modules/task_2/vodeneev_m_jarvis/jarvis.h"

std::vector<std::pair<double, double>> GetPoints(int left_border, int right_border,
    int low_border, int high_border, size_t size) {

    srand(time(NULL));

    std::vector<std::pair<double, double>> res(size);
    for (size_t i = 0; i < size; i++) {
        res[i].first = left_border + static_cast<double>(std::rand()) / RAND_MAX * (right_border - left_border);
        res[i].second = low_border + static_cast<double>(std::rand()) / RAND_MAX * (high_border - low_border);
    }

    return res;
}

double OrientationPointRelativeToVector(std::pair<double, double> A,
    std::pair<double, double> B, std::pair<double, double> point) {

    return (B.first - A.first) * (point.second - B.second)
        - (B.second - A.second) * (point.first - B.first);
}

std::vector<std::pair<double, double>> JarvisSeq(std::vector<std::pair
    <double, double>> points) {
    if (points.size() < 1)
        throw - 1;

    std::pair<double, double> left_point = points[0];
    int current_index = 0;
    for (size_t i = 0; i < points.size(); i++) {
        if (points[i].first < left_point.first) {
            left_point = points[i];
            current_index = i;
        }
    }

    std::vector<std::pair<double, double>> hull;
    hull.push_back(left_point);

    points.erase(points.begin() + current_index);
    points.push_back(left_point);

    while (true) {
        size_t next_point = 0;
        for (size_t i = 0; i < points.size(); i++) {
            if (OrientationPointRelativeToVector(hull.back(), points[next_point], points[i]) < 0) {
                next_point = i;
            }
        }

        if (points[next_point] == hull[0]) {
            return hull;
        } else {
            hull.push_back(points[next_point]);
            points.erase(points.begin() + next_point);
        }
    }
}

std::vector<std::pair<double, double>> JarvisOmp(std::vector<std::pair
    <double, double>> points, int numthreads) {
    int set_size = points.size();
    if (set_size < 1)
        throw - 1;

    std::pair<double, double> left_point = points[0];
    int current_index = 0;

    for (size_t i = 0; i < points.size(); i++) {
       if (points[i].first < left_point.first) {
          left_point = points[i];
          current_index = i;
       }
    }

    std::vector<std::pair<double, double>> hull;
    hull.push_back(left_point);

    points.erase(points.begin() + current_index);
    points.push_back(left_point);
    int next_point = 0;

    std::vector<int> indexes(numthreads);

    while (true) {
#pragma omp parallel num_threads(numthreads)
{
            int temp_index = 0;

#pragma omp for
            for (int i = 0; i < set_size; i++) {
                if (OrientationPointRelativeToVector(hull.back(), points[temp_index], points[i]) < 0) {
                    temp_index = i;
                }
            }

            indexes[omp_get_thread_num()] = temp_index;
        }

        sort(indexes.begin(), indexes.end());

        next_point = indexes[0];

        for (uint64_t i = 0; i < indexes.size(); i++) {
            if (OrientationPointRelativeToVector(hull.back(), points[next_point], points[indexes[i]]) < 0) {
                next_point = indexes[i];
            }
        }

        if (points[next_point] != hull[0]) {
            hull.push_back(points[next_point]);
            points.erase(points.begin() + next_point);
            set_size--;
        } else {
            return hull;
        }
    }
}
