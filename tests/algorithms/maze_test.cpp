#include <gtest/gtest.h>

#include <algorithms/Maze.hpp>
#include <algorithms/Vector.hpp>

using namespace maze;

class MazeTest : public ::testing::Test {
  protected:
   Maze maze;

   VectorULL default_size{0, 0};
   VectorULL custom_size{5, 5};

   void SetUp() override { maze.Resize(custom_size); }
};

TEST_F(MazeTest, DefaultConstructor) {
   Maze default_maze;
   EXPECT_EQ(default_maze.GetSize(), default_size);
}

TEST_F(MazeTest, CustomConstructor) {
   Maze custom_maze(custom_size);
   EXPECT_EQ(custom_maze.GetSize(), custom_size);
}

TEST_F(MazeTest, ResizeMaze) {
   VectorULL new_size{10, 10};
   maze.Resize(new_size);
   EXPECT_EQ(maze.GetSize(), new_size);
}

TEST_F(MazeTest, ResetMaze) {
   maze.Set({1, 1}, Maze::ObjectType::WALL);
   maze.Reset();
   EXPECT_EQ(maze.Get({1, 1}), Maze::ObjectType::ROAD);
}

TEST_F(MazeTest, SetAndGetObjectType) {
   maze.Set({1, 1}, Maze::ObjectType::ROAD);
   EXPECT_EQ(maze.Get({1, 1}), Maze::ObjectType::ROAD);

   maze.Set({2, 2}, Maze::ObjectType::WALL);
   EXPECT_EQ(maze.Get({2, 2}), Maze::ObjectType::WALL);
}

TEST_F(MazeTest, SetAndGetStartPoint) {
   VectorULL start_point{0, 0};
   maze.Set(start_point, Maze::ObjectType::START_POINT);
   auto result = maze.GetStartPoint();
   ASSERT_TRUE(result.has_value());
   EXPECT_EQ(result.value(), start_point);
}

TEST_F(MazeTest, SetAndGetEndPoint) {
   VectorULL end_point{4, 4};
   maze.Set(end_point, Maze::ObjectType::END_POINT);
   auto result = maze.GetEndPoint();
   ASSERT_TRUE(result.has_value());
   EXPECT_EQ(result.value(), end_point);
}

TEST_F(MazeTest, IndexOutOfRange) {
   EXPECT_THROW(maze.Get({10, 10}), std::out_of_range);
   EXPECT_THROW(maze.Set({10, 10}, Maze::ObjectType::WALL), std::out_of_range);
}

TEST_F(MazeTest, InvalidStartPoint) {
   VectorULL invalid_start_point{0, 0};
   maze.Set(invalid_start_point, Maze::ObjectType::WALL);
   auto result = maze.GetStartPoint();
   EXPECT_FALSE(result.has_value());
}

TEST_F(MazeTest, InvalidEndPoint) {
   VectorULL invalid_end_point{4, 4};
   maze.Set(invalid_end_point, Maze::ObjectType::ROAD);
   auto result = maze.GetEndPoint();
   EXPECT_FALSE(result.has_value());
}
