#include <algorithms/A.hpp>

#include <queue>
#include <unordered_map>

namespace maze {

Path AStar::Run(const maze::Maze& maze) {
   Path result;

   auto start = maze.GetStartPoint();
   auto end = maze.GetEndPoint();
   if (!start || !end) {
      return result;  // No start or end point defined
   }

   std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open_set;
   std::unordered_map<maze::VectorULL, double> g_costs;
   std::unordered_map<maze::VectorULL, std::optional<maze::VectorULL>>
      came_from;

   maze::VectorULL start_pos = *start;
   maze::VectorULL end_pos = *end;

   open_set.push({start_pos, 0.0, Heuristic(start_pos, end_pos),
                  Heuristic(start_pos, end_pos)});
   g_costs[start_pos] = 0.0;

   while (!open_set.empty()) {
      Node current = open_set.top();
      open_set.pop();

      if (current.position == end_pos) {
         maze::VectorULL step = end_pos;
         while (step != start_pos) {
            result.SetNext(step);
            step = *came_from[step];
         }
         result.SetNext(start_pos);
         return result;  // Path found
      }

      for (const maze::VectorULL& neighbor :
           GetNeighbors(maze, current.position)) {
         double tentative_g_cost = g_costs[current.position] + 1.0;

         if (g_costs.find(neighbor) == g_costs.end() ||
             tentative_g_cost < g_costs[neighbor]) {
            came_from[neighbor] = current.position;
            g_costs[neighbor] = tentative_g_cost;
            double h_cost = Heuristic(neighbor, end_pos);
            double f_cost = tentative_g_cost + h_cost;

            open_set.push({neighbor, tentative_g_cost, h_cost, f_cost});
         }
      }
   }

   return result;  // No path found
}

double AStar::Heuristic(const maze::VectorULL& a,
                        const maze::VectorULL& b) const {
   // Manhattan distance as the heuristic
   return std::abs(static_cast<double>(a.x) - b.x) +
          std::abs(static_cast<double>(a.y) - b.y);
}

std::vector<maze::VectorULL> AStar::GetNeighbors(
   const maze::Maze& maze, const maze::VectorULL& pos) const {
   std::vector<maze::VectorULL> neighbors;
   maze::VectorI directions[] = {
      {0, 1}, {1, 0}, {0, -1}, {-1, 0}  // Up, right, down, left
   };

   for (const auto& dir : directions) {
      maze::VectorULL neighbor = {pos.x + dir.x, pos.y + dir.y};

      if (neighbor.x >= 0 && neighbor.x < maze.GetSize().x && neighbor.y >= 0 &&
          neighbor.y < maze.GetSize().y &&
          maze.Get(neighbor) != maze::Maze::ObjectType::WALL) {
         neighbors.push_back(neighbor);
      }
   }

   return neighbors;
}
}  // namespace maze