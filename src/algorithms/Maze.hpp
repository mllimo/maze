#pragma once

#include <optional>
#include <vector>

#include <algorithms/Vector.hpp>

namespace maze {
class Maze {
  public:
   enum class ObjectType { UNDEFINED, ROAD, WALL, START_POINT, END_POINT };

   Maze() = default;
   Maze(const VectorULL& size);

   ~Maze() = default;

   void Resize(const VectorULL& size);
   void Reset();
   void Set(const VectorULL& at, ObjectType element);

   ObjectType Get(const VectorULL& at) const;
   std::optional<VectorULL> GetStartPoint() const;
   std::optional<VectorULL> GetEndPoint() const;
   VectorULL GetSize() const;

  private:
   std::optional<VectorULL> _start_point;
   std::optional<VectorULL> _end_point;

   VectorULL _size = {0, 0};
   std::vector<ObjectType> _maze;

   size_t Index(const VectorULL& pos) const;
};
}  // namespace maze
