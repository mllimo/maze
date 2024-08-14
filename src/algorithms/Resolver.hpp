#pragma once

#include <algorithms/Algorithm.hpp>
#include <algorithms/Maze.hpp>
#include <algorithms/Path.hpp>

namespace maze {
class Resolver {
  public:
   virtual Path Resolve(const Maze& maze, Algorithm* algorithm);
};
}  // namespace maze