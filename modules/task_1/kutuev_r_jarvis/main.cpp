// Copyright 2022 Kutuev Roman
#include <gtest/gtest.h>

#include "../../../modules/task_1/kutuev_r_jarvis/jarvis.h"
TEST(Jarvis, test_1) {
  jarvis quick_hull;
  std::vector<Point> quick = quick_hull.convex_hull(quick_hull.set_points(2));
  EXPECT_DOUBLE_EQ(quick.size(), 0);
}

TEST(Jarvis, test_2) {
  jarvis quick_hull;
  std::vector<Point> polygon{{1, 1}, {2, 2}, {2, 1}, {1, 2}};
  std::vector<Point> quick = quick_hull.convex_hull(polygon);

  EXPECT_DOUBLE_EQ(quick[0].x, polygon[0].x);
  EXPECT_DOUBLE_EQ(quick[0].y, polygon[0].y);
  EXPECT_DOUBLE_EQ(quick[1].x, polygon[2].x);
  EXPECT_DOUBLE_EQ(quick[1].y, polygon[2].y);
  EXPECT_DOUBLE_EQ(quick[2].x, polygon[1].x);
  EXPECT_DOUBLE_EQ(quick[2].y, polygon[1].y);
  EXPECT_DOUBLE_EQ(quick[3].x, polygon[3].x);
  EXPECT_DOUBLE_EQ(quick[3].y, polygon[3].y);
}
TEST(Jarvis, test_3) {
  jarvis quick_hull;
  std::vector<Point> polygon{{1, 1}, {3, 1}, {3, 2}, {3, 3}, {2, 3}, {1, 3}};
  std::vector<Point> quick = quick_hull.convex_hull(polygon);

  EXPECT_DOUBLE_EQ(quick[0].x, polygon[0].x);
  EXPECT_DOUBLE_EQ(quick[0].y, polygon[0].y);
  EXPECT_DOUBLE_EQ(quick[1].x, polygon[1].x);
  EXPECT_DOUBLE_EQ(quick[1].y, polygon[1].y);
  EXPECT_DOUBLE_EQ(quick[2].x, polygon[3].x);
  EXPECT_DOUBLE_EQ(quick[2].y, polygon[3].x);
  EXPECT_DOUBLE_EQ(quick[3].x, polygon[5].x);
  EXPECT_DOUBLE_EQ(quick[3].y, polygon[5].y);
}
TEST(Jarvis, test_4) {
  jarvis quick_hull;
  std::vector<Point> polygon{{249, 106}, {419, 341}, {168, 227}, {176, 145},
                             {228, 309}, {449, 247}, {260, 98},  {264, 368},
                             {208, 286}, {365, 0}};
  std::vector<Point> quick = quick_hull.convex_hull(polygon);
  EXPECT_DOUBLE_EQ(quick[0].x, polygon[2].x);
  EXPECT_DOUBLE_EQ(quick[0].y, polygon[2].y);
  EXPECT_DOUBLE_EQ(quick[1].x, polygon[3].x);
  EXPECT_DOUBLE_EQ(quick[1].y, polygon[3].y);
  EXPECT_DOUBLE_EQ(quick[2].x, polygon[9].x);
  EXPECT_DOUBLE_EQ(quick[2].y, polygon[9].y);
  EXPECT_DOUBLE_EQ(quick[3].x, polygon[5].x);
  EXPECT_DOUBLE_EQ(quick[3].y, polygon[5].y);
  EXPECT_DOUBLE_EQ(quick[4].x, polygon[1].x);
  EXPECT_DOUBLE_EQ(quick[4].y, polygon[1].y);
  EXPECT_DOUBLE_EQ(quick[5].x, polygon[7].x);
  EXPECT_DOUBLE_EQ(quick[5].y, polygon[7].y);
  EXPECT_DOUBLE_EQ(quick[6].x, polygon[8].x);
  EXPECT_DOUBLE_EQ(quick[6].y, polygon[8].y);
}

TEST(Jarvis, test_5) {
  jarvis quick_hull;
  auto time1 = clock();
  std::vector<Point> quick = quick_hull.convex_hull(quick_hull.set_points(1));
  auto time2 = clock();
  printf("time : %f\n\n", static_cast<float>(time2 - time1) / CLOCKS_PER_SEC);
}
