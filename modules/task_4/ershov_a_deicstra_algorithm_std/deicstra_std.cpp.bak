// Copyright 2022 Ershov Aleksey
#include "./deicstra_tbb.h"

#include <tbb/tbb.h>

#include <algorithm>
#include <random>
#include <utility>
#include <vector>

std::vector<std::vector<int>> getRandomVector(const int count) {
  std::vector<std::vector<int>> graf(count, std::vector<int>(count));
  std::mt19937 gen(0);
  for (int i = 0; i < count; ++i) {
    graf[i][i] = 0;
    for (int j = i + 1; j < count; ++j) {
      graf[i][j] = gen() % 100;
      graf[j][i] = graf[i][j];
    }
  }
  return graf;
}

std::vector<int> getDeicstra(const std::vector<std::vector<int>>& graf,
                             const int top) {
  const int count = graf.size();
  std::vector<bool> visitedTops(count);
  std::vector<int> dist(count, 10000);
  dist[top] = 0;
  int min_dist = 0;
  int min_vertex = top;

  while (min_dist < 10000) {
    int i = min_vertex;
    visitedTops[i] = true;
    for (int j = 0; j < count; ++j)
      if ((dist[i] + graf[i][j] < dist[j]) && (graf[i][j] != 0))
        dist[j] = dist[i] + graf[i][j];
    min_dist = 10000;
    for (int j = 0; j < count; ++j)
      if (!visitedTops[j] && dist[j] < min_dist) {
        min_dist = dist[j];
        min_vertex = j;
      }
  }

  return dist;
}

std::vector<int> getSequentialDeicstra(
    const std::vector<std::vector<int>>& graf) {
  int top = 0;
  const int count = graf.size();
  std::vector<int> result(count * count, 0);
  for (top = 0; top < count; ++top) {
    auto tmp = getDeicstra(graf, top);
    for (int i = 0; i < count; ++i) {
      result[top * count + i] = tmp[i];
    }
  }
  return result;
}

std::vector<int> getParallelDeicstra(
    const std::vector<std::vector<int>>& graf) {
  int numThreads = 6;
  int count = graf.size();
  int grainSize = count / numThreads;
  std::vector<int> result(graf.size() * graf.size(), 0);
  tbb::task_scheduler_init init(numThreads);

  tbb::parallel_for(tbb::blocked_range<int>(0, count, grainSize),
                    Deicstor(graf, &result));

  return result;
}

void Deicstor::operator()(const tbb::blocked_range<int>& r) const {
  int begin = r.begin();
  int end = r.end();
  int count = graf.size();
  for (int top = begin; top < end; ++top) {
    auto tmp = getDeicstra(graf, top);
    for (int i = 0; i < count; ++i) {
      (*result)[top * count + i] = tmp[i];
    }
  }
}
