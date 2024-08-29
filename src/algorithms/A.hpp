#pragma once

#include <algorithms/Algorithm.hpp>

namespace maze {
class AStar : public Algorithm {
  public:
   Path Run(const Maze& maze) override;

   struct Node {
      VectorULL position;
      double g_cost;  // Cost from start to current node
      double h_cost;  // Heuristic cost to the goal
      double f_cost;  // Total cost (g_cost + h_cost)
      std::optional<VectorULL> parent;

      bool operator>(const Node& other) const { return f_cost > other.f_cost; }
   };

   double Heuristic(const VectorULL& a, const VectorULL& b) const;
   std::vector<VectorULL> GetNeighbors(const maze::Maze& maze,
                                       const VectorULL& pos) const;
};
}  // namespace maze