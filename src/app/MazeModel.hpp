#pragma once

#include <filesystem>

#include <algorithms/Maze.hpp>
#include "algorithms/Vector.hpp"

namespace app {
class MazeModel {
  public:
   void LoadFromFile(std::filesystem::path path);
   void AddElement(const maze::VectorULL& pos, maze::Maze::ObjectType element);
   void Resize(const maze::VectorULL& pos);
   void Reset();

   const maze::Maze& GetMaze() const;

  private:
   maze::Maze _maze;
};
}  // namespace app