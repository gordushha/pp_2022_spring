// Copyright 2022 Zaitseva Ksenia
#include <gtest/gtest.h>
#include <vector>
#include "./jarvis.h"

TEST(Sequential, Test_Point_equal) {
  Point p1 = {0.2, 0.1};
  Point p2 = p1;
  ASSERT_TRUE(p2 == p1);
}

TEST(Sequential, Test_Point_less) {
  Point p1 = {0.2, 0.1};
  Point p2 = {-1.4, 0.0};
  ASSERT_TRUE(p2 < p1);
}

TEST(Sequential, Test_Point_minus) {
  Point p1 = {0.2, 0.1};
  Point p2 = {-1.4, 0.0};
  Point p3 = p1 - p2;
  EXPECT_EQ(Point(1.6, 0.1), p3);
}

TEST(Sequential, Test_Calc_Determinant) {
  Point p1 = {1.0, -2.0};
  Point p2 = {-1.0, 0.0};
  EXPECT_EQ(-2.0, cross(p1, p2));
}

TEST(Sequential, Test_and_Draw) {
  std::vector<Point> points = {{2.0, 1.0}, {-0.5, 1.0}, {-3.0, -1.5},
                               {3.5, 1.0}, {0.5, 4.0},  {-4.5, -3.0},
                               {-2.5, 3.5}};
  std::vector<Point> res = Jarvis(points);
  std::vector<Point> expected_res = {
      {-4.5, -3}, {3.5, 1}, {0.5, 4}, {-2.5, 3.5}};
  EXPECT_EQ(res, expected_res);
}

TEST(Sequential, Test_Generate_and_Draw) {
  std::vector<Point> points = Generate(10);
  std::ofstream fout("shell.txt");
  std::ofstream fout2("points.txt");
  std::vector<Point> res = Jarvis(points);
  for (std::size_t i = 0; i < res.size(); i++)
    fout << res[i].x << std::endl << res[i].y << std::endl;
  fout << res[0].x << std::endl << res[0].y << std::endl;
  for (auto i = points.begin(); i != points.end(); i++)
    fout2 << i->x << std::endl << i->y << std::endl;
  fout.close();
  fout2.close();
}
