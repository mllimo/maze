#include <app/MazeModel.hpp>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <ios>
#include <stdexcept>
#include "algorithms/Maze.hpp"
#include "algorithms/Vector.hpp"

namespace app {
void MazeModel::LoadFromFile(std::filesystem::path path) {
   if (not std::filesystem::exists(path))
      throw std::invalid_argument("Maze file path does not exist");

   std::ifstream file(path.c_str(), std::ios_base::binary);

   maze::VectorULL size;
   file >> size.x >> size.y;
   _maze = maze::Maze(size);

   for (size_t i = 0; i < size.x; ++i) {
      for (size_t j = 0; j < size.y; ++j) {
         char element_char;
         maze::Maze::ObjectType element;
         file >> element_char;

         switch (element_char) {
            case '0':
               element = maze::Maze::ObjectType::ROAD;
               break;
            case 'W':
               element = maze::Maze::ObjectType::WALL;
               break;
            case 'S':
               element = maze::Maze::ObjectType::START_POINT;
               break;
            case 'E':
               element = maze::Maze::ObjectType::END_POINT;
               break;
            default:
               throw std::invalid_argument("Invalid element in maze file");
         }

         _maze.Set({j, i}, element);
      }
   }
}

void MazeModel::AddElement(const maze::VectorULL& pos,
                           maze::Maze::ObjectType element) {
   _maze.Set(pos, element);
}

void MazeModel::Resize(const maze::VectorULL& size) {
   _maze.Resize(size);
}

void MazeModel::Reset() {
   _maze.Reset();
}

const maze::Maze& MazeModel::GetMaze() const {
   return _maze;
}
}  // namespace app