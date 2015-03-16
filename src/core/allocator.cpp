#include "allocator.hpp"

namespace Vole {

  char* Allocator::alloc_string(size_t size, char color) {
    ++size;
    char* mem = new char[size];
    objects.push_front(Value(String(mem, mem, size, size)));
    *mem = color;
    return mem + 1;
  }

  Value* Allocator::alloc_vector(size_t size, char color) {
    ++size;
    Value* mem = new Value[size];
    objects.push_front(Value(Vector(mem, mem, size, size)));
    *mem = Value(color);
    return mem + 1;
  }

  Allocator::~Allocator() {
    // std::cout << std::endl << "DELETING ALL ALLOCATIONS:" << std::endl;
    for (auto val : objects) {
      // if (val.type == Value::STRING) {
      //   std::cout << '[' << *val.content.string.mem << "] ";
      //   std::cout << val.content.string.tail() << std::endl;
      // } else if (val.type == Value::VECTOR) {
      //   std::cout << *val.content.vector.mem << ' ';
      //   std::cout << val.content.vector.tail() << std::endl;
      // }
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

}