#include <algorithms/Path.hpp>

namespace maze {
void Path::SetNext(const VectorULL& step) {
   _steps.push_back(step);
}

Path::const_iterator Path::cbegin() const {
   return _steps.cbegin();
}

Path::const_iterator Path::cend() const {
   return _steps.cend();
}
}  // namespace maze