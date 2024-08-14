#include <algorithms/Maze.hpp>
#include <stdexcept>
#include <vector>

namespace maze {
Maze::Maze(const VectorULL& size)
    : _size(size), _maze(size.x * size.y, ObjectType::ROAD) {}

void Maze::Resize(const VectorULL& size) {
   size_t new_total_size = size.x * size.y;
   size_t this_total_size = _size.x * _size.y;

   if (this_total_size > new_total_size) {
      _size = size;

      if (_start_point.has_value() && (_start_point.value().x >= size.x ||
                                       _start_point.value().y >= size.y)) {
         // the stored start point is out the maze
         _start_point = {};
      }

      if (_end_point.has_value() &&
          (_end_point.value().x >= size.x || _end_point.value().y >= size.y)) {
         // the stored end point is out the maze
         _end_point = {};
      }
   }

   std::vector<ObjectType> new_maze(size.x * size.y, ObjectType::ROAD);

   for (size_t i = 0; i < size.y; ++i) {
      for (size_t j = 0; j < size.x; ++j) {
         if (i < _size.x && j < _size.y) {
            new_maze[size.x * i + j] = _maze[Index({j, i})];
         }
      }
   }

   _size = size;
   _maze = std::move(new_maze);
}

void Maze::Reset() {
   for (ObjectType& element : _maze)
      element = ObjectType::ROAD;

   _start_point = {};
   _end_point = {};
}

void Maze::Set(const VectorULL& at, ObjectType element) {
   if (at.x >= _size.x && at.y >= _size.y)
      throw std::invalid_argument("invalid maze position");

   if (element == ObjectType::START_POINT)
      _start_point = at;

   if (element == ObjectType::END_POINT)
      _end_point = at;

   _maze[Index(at)] = element;
}

Maze::ObjectType Maze::Get(const VectorULL& at) const {
   if (at.x >= _size.x && at.y >= _size.y)
      throw std::invalid_argument("invalid maze position");

   return _maze[Index(at)];
}

std::optional<VectorULL> Maze::GetStartPoint() const {
   return _start_point;
}

std::optional<VectorULL> Maze::GetEndPoint() const {
   return _end_point;
}

VectorULL Maze::GetSize() const {
   return _size;
}

size_t Maze::Index(const VectorULL& pos) const {
   return _size.x * pos.y + pos.x;
}

}  // namespace maze