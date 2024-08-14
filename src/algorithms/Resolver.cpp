#include <algorithms/Resolver.hpp>

namespace maze {
Path Resolver::Resolve(const Maze& maze, Algorithm* algorithm) {
   return algorithm->Run(maze);
}
}  // namespace maze