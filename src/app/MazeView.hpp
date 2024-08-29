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

   void SetColorOf(maze::Maze::ObjectType object, Color color);
   void SetColorDefault();

  private:
   const maze::Maze* _maze_ptr = nullptr;

   maze::VectorULL _cell_size = {20, 20};
   Color _undefined = WHITE;
   Color _road_color = GRAY;
   Color _wall_color = BLACK;
   Color _start_color = YELLOW;
   Color _end_color = RED;
};
}  // namespace app