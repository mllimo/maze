#pragma once

#include <list>

#include <algorithms/Vector.hpp>

namespace maze {
class Path {
  public:
   using const_iterator = std::list<VectorULL>::const_iterator;

   Path() = default;
   ~Path() = default;

   void SetNext(const VectorULL& step);

   const_iterator cbegin() const;
   const_iterator cend() const;

  private:
   std::list<VectorULL> _steps;
};
}  // namespace maze