#pragma once

#include <raylib.h>
#include <app/MazeModel.hpp>
#include <app/MazeView.hpp>

namespace app {
class MazeController {
  public:
   MazeController() = default;

   void Init(const std::filesystem::path& file_path);
   void Display();

   void LoadFromFile(std::filesystem::path path);
   void AddElement(const maze::VectorULL& pos, maze::Maze::ObjectType element);
   void Resize(const maze::VectorULL& size);
   void Reset();

   std::optional<maze::VectorULL> CellClicked(Vector2 pos);

  private:
   MazeModel model;
   MazeView view;
};
}  // namespace app