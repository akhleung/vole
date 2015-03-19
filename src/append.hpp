#ifndef VOLE_SLICE_OPS
#define VOLE_SLICE_OPS

#include "slice.hpp"
#include <initializer_list>

namespace Vole {

  class Allocator;

  template <typename T>
  Slice<T> append(Allocator& alloc, Slice<T> s, T t);

  template <typename T>
  Slice<T> append(Allocator& alloc, Slice<T> s1, Slice<T> s2);

}

#endif