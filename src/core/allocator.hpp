#ifndef VOLE_ALLOCATOR
#define VOLE_ALLOCATOR

#include <forward_list>
#include "value.hpp"

namespace Vole {

  class Allocator {
    std::forward_list<Value> objects;
  public:
    char*  alloc_string(size_t size, char color = 'w');
    Value* alloc_vector(size_t size, char color = 'w');
    ~Allocator();
  };

}

#endif
