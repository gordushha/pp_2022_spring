
// Copyright 2022 Kutuev Roman

#include "../../../modules/task_2/kutuev_r_jarvis/jarvis.h"
static const int NUM_THREADS = 12;

std::vector<Point> set_points(int size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_real_distribution<> urd(-1000, 1000);
    std::vector<Point> points(size);
    for (int i = 0; i < size; i++) {
        points[i].set_point(urd(gen), urd(gen));
    }
    return points;
}

int find_lowest_left_most_point_index(const std::vector<Point>& points) {
    int index = 0;
    int min_x = points[0].x;
    int min_y = points[0].y;
    int size = points.size();
    for (int i = 1; i < size; i++) {
        if (points[i].x < min_x ||
            (points[i].x == min_x && points[i].y < min_y)) {
            min_x = points[i].x;
            min_y = points[i].y;
            index = i;
        }
    }
    return index;
}


int orientation(const Point& p0, const Point& p1, const Point& p2) {
    int value = (p1.x * p2.y - p2.x * p1.y) - (p0.x * p2.y - p2.x * p0.y) +
        (p0.x * p1.y - p0.y * p1.x);

    if (value == 0)
        return collinear;
    else if (value > 0)
        return right;
    else
        return left;
}

int sq_distance(const Point& p0, const Point& p1) {
    return (p0.x - p1.x) * (p0.x - p1.x) + (p0.y - p1.y) * (p0.y - p1.y);
}

std::vector<Point> convex_hull(const std::vector<Point>& points) {
    std::vector<Point> input = points;
    int size = points.size();
    std::vector<Point> CH;
    if (size < 3) return CH;
    int current, next, sign;
    int bottom_left_point_idx = find_lowest_left_most_point_index(input);
    current = bottom_left_point_idx;
    do {
        CH.push_back(input[current]);
        next = (current + 1) % size;
        for (int i = size - 1; i >= 0; i--)
            if (input[i].x != input[current].x || input[i].y != input[current].y) {
                sign = orientation(input[current], input[i], input[next]);
                if (sign == right ||
                    (sign == collinear && sq_distance(input[current], input[next]) <
                        sq_distance(input[current], input[i])))
                    next = i;
            }
        current = next;
    } while (input[current].x != input[bottom_left_point_idx].x ||
        input[current].y != input[bottom_left_point_idx].y);
    return CH;
}

std::vector<Point> convex_hull_omp(const std::vector<Point>& points) {
    std::vector<Point> input = points;
    int size = points.size();
    std::vector<Point> CH;
    if (size < 3) return CH;
    int current, next, sign;
    int bottom_left_point_idx = 0;
    int i;
    omp_lock_t lock;
    omp_init_lock(&lock);
#pragma omp parallel for shared( \
    input, size, bottom_left_point_idx) private(i) num_threads(NUM_THREADS)
    for (i = 0; i < size; i++) {
        if (input[i].x < input[bottom_left_point_idx].x ||
            (input[i].x == input[bottom_left_point_idx].x &&
                input[i].y < input[bottom_left_point_idx].y)) {
            omp_set_lock(&lock);
            if (input[i].x < input[bottom_left_point_idx].x ||
                (input[i].x == input[bottom_left_point_idx].x &&
                    input[i].y < input[bottom_left_point_idx].y))
                bottom_left_point_idx = i;
            omp_unset_lock(&lock);
        }
    }
    current = bottom_left_point_idx;
    do {
        CH.push_back(input[current]);
        next = (current + 1) % size;
#pragma omp parallel for shared(input, size, next) private(i, sign) \
    num_threads(NUM_THREADS)
        for (i = size - 1; i >= 0; i--) {
            if (input[i].x != input[current].x ||
                input[i].y != input[current].y) {
                sign = orientation(input[current], input[i], input[next]);
                if (sign == right ||
                    (sign == collinear && sq_distance(input[current], input[next]) <
                        sq_distance(input[current], input[i]))) {
                    omp_set_lock(&lock);
                    sign = orientation(input[current], input[i], input[next]);
                    if (sign == right ||
                        (sign == collinear && sq_distance(input[current], input[next]) <
                            sq_distance(input[current], input[i])))
                        next = i;
                    omp_unset_lock(&lock);
                }
            }
        }
        current = next;
    } while (input[current].x != input[bottom_left_point_idx].x ||
        input[current].y != input[bottom_left_point_idx].y);
    return CH;
}
