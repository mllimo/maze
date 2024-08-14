#pragma once

#include <algorithms/Algorithm.hpp>

namespace maze {
class AStar : public Algorithm {
  public:
   Path Run(const Maze& maze) override;
};
}  // namespace maze