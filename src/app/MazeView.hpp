#pragma once

#include <raylib.h>
#include "algorithms/Maze.hpp"
#include "algorithms/Vector.hpp"

namespace app {
class MazeView {
  public:
   void UpdateMazeRef(const maze::Maze* maze_ptr);
   void Display() const;

   std::optional<maze::VectorULL> CellClicked(Vector2 pos);

  private:
   const maze::Maze* _maze_ptr = nullptr;

   maze::VectorULL _cell_size = {20, 20};
   Color _road_color = WHITE;
   Color _wall_color = BLACK;
   Color _start_color = YELLOW;
   Color _end_color = RED;
};
}  // namespace app