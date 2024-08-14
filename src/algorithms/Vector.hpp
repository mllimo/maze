#pragma once

#include <bitset>

namespace maze {
template <typename T>
struct Vector {
   T x;
   T y;

   friend bool operator==(const Vector<T>& a, const Vector<T>& b) {
      return a.x == b.x && a.y == b.y;
   }
};

typedef Vector<int> VectorI;
typedef Vector<unsigned> VectorU;
typedef Vector<size_t> VectorULL;
}  // namespace maze

namespace std {
template <typename T>
struct hash<maze::Vector<T>> {
   std::size_t operator()(const maze::Vector<T>& v) const noexcept {
      std::size_t h1 = std::hash<T>{}(v.x);
      std::size_t h2 = std::hash<T>{}(v.y);
      return h1 ^ (h2 << 1);  // Mezclar los hashes
   }
};
}  // namespace std