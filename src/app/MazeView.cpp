#include <raylib.h>
#include <app/MazeView.hpp>
#include <optional>
#include "algorithms/Vector.hpp"

namespace app {
void MazeView::UpdateMazeRef(const maze::Maze* maze_ptr) {
   _maze_ptr = maze_ptr;
}

void MazeView::Display() const {
   Rectangle rectangle_to_draw = {.x = 0,
                                  .y = 0,
                                  .width = (float)_cell_size.x,
                                  .height = (float)_cell_size.y};
   Color color = GREEN;

   for (size_t i = 0; i < _maze_ptr->GetSize().y; ++i) {
      for (size_t j = 0; j < _maze_ptr->GetSize().x; ++j) {
         auto element = _maze_ptr->Get({j, i});

         switch (element) {
            case maze::Maze::ObjectType::UNDEFINED:
               color = _undefined;
               break;
            case maze::Maze::ObjectType::ROAD:
               color = _road_color;
               break;
            case maze::Maze::ObjectType::WALL:
               color = _wall_color;
               break;
            case maze::Maze::ObjectType::START_POINT:
               color = _start_color;
               break;
            case maze::Maze::ObjectType::END_POINT:
               color = _end_color;
               break;
         }

         rectangle_to_draw.x = _cell_size.x * j;
         rectangle_to_draw.y = _cell_size.y * i;
         DrawRectangleRec(rectangle_to_draw, color);
      }
   }
}

std::optional<maze::VectorULL> MazeView::CellClicked(Vector2 pos) {
   Rectangle cell = {.x = 0,
                     .y = 0,
                     .width = (float)_cell_size.x,
                     .height = (float)_cell_size.y};

   for (size_t i = 0; i < _maze_ptr->GetSize().y; ++i) {
      for (size_t j = 0; j < _maze_ptr->GetSize().x; ++j) {
         cell.x = _cell_size.x * j;
         cell.y = _cell_size.y * i;
         if (CheckCollisionPointRec(pos, cell))
            return maze::VectorULL{j, i};
      }
   }

   return std::nullopt;
}

void MazeView::SetColorOf(maze::Maze::ObjectType object, Color color) {
   switch (object) {
      case maze::Maze::ObjectType::UNDEFINED:
         _undefined = color;
         break;
      case maze::Maze::ObjectType::ROAD:
         _road_color = color;
         break;
      case maze::Maze::ObjectType::WALL:
         _wall_color = color;
         break;
      case maze::Maze::ObjectType::START_POINT:
         _start_color = color;
         break;
      case maze::Maze::ObjectType::END_POINT:
         _end_color = color;
         break;
   }
}

void MazeView::SetColorDefault() {
   _undefined = WHITE;
   _road_color = GRAY;
   _wall_color = BLACK;
   _start_color = YELLOW;
   _end_color = RED;
}

}  // namespace app