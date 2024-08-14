#pragma once

#include <algorithms/Maze.hpp>
#include <algorithms/Path.hpp>

namespace maze {
class Algorithm {
  public:
   virtual Path Run(const Maze& maze) = 0;
};
}  // namespace maze