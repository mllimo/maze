#include <app/MazeController.hpp>

namespace app {
void MazeController::Init(const std::filesystem::path& file_path) {
   model.LoadFromFile(file_path);
}

void MazeController::Display() {
   view.UpdateMazeRef(&model.GetMaze());
   view.Display();
}

void MazeController::LoadFromFile(std::filesystem::path path) {
   model.LoadFromFile(path);
}

void MazeController::AddElement(const maze::VectorULL& pos,
                                maze::Maze::ObjectType element) {
   model.AddElement(pos, element);
}

void MazeController::Resize(const maze::VectorULL& size) {
   model.Resize(size);
}

void MazeController::Reset() {
   model.Reset();
}

const maze::Maze& MazeController::GetMaze() const {
   return model.GetMaze();
}

void MazeController::SetColorOf(maze::Maze::ObjectType object, Color color) {
   view.SetColorOf(object, color);
}

void MazeController::SetColorDefault() {
   view.SetColorDefault();
}

std::optional<maze::VectorULL> MazeController::CellClicked(Vector2 pos) {
   view.UpdateMazeRef(&model.GetMaze());
   return view.CellClicked(pos);
}

}  // namespace app