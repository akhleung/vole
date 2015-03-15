#ifndef VOLE_ALLOCATOR
#define VOLE_ALLOCATOR

#include <cstdlib>
#include <forward_list>
#include "slice.hpp"
#include "value.hpp"

namespace Vole {

  class Allocator {

    std::forward_list<Value> objects;

  public:

    template <typename T>
    T* alloc(size_t size);

    ~Allocator() {
      for (auto val : objects) {
        switch (val.type) {
          case Value::STRING:
            delete val.content.string.mem;
            break;
          case Value::VECTOR:
            delete val.content.vector.mem;
            break;
          default:
            break; // don't forget the other types once they're implemented
        }
      }
    }

  };

  template <>
  char* Allocator::alloc(size_t size) {
    char* mem = new char[size];
    objects.push_front(Value(String(mem, mem, size, size)));
    return mem;
  }

  template <>
  Value* Allocator::alloc(size_t size) {
    Value* mem = new Value[size];
    objects.push_front(Value(Vector(mem, mem, size, size)));
    return mem;
  }

}

#endif
