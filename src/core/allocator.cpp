#include "allocator.hpp"
#include "value.hpp"

namespace Vole {

  Allocator::Handle::Object::Object(char* ptr) : char_ptr(ptr) { }
  Allocator::Handle::Object::Object(Value* ptr) : value_ptr(ptr) { }

  Allocator::Handle::Handle(Type t, char* ptr)
  : type(t), object(ptr)
  { }
  Allocator::Handle::Handle(Type t, Value* ptr)
  : type(t), object(ptr)
  { }

  char* Allocator::alloc_string(size_t size, char color) {
    ++size;
    char* mem = new char[size];
    handles.push_front(Handle(Handle::CHAR, mem));
    *mem = color;
    return mem + 1;
  }

  Value* Allocator::alloc_vector(size_t size, char color) {
    ++size;
    Value* mem = new Value[size];
    handles.push_front(Handle(Handle::VALUE, mem));
    *mem = Value(color);
    return mem + 1;
  }

  Allocator::~Allocator() {
    // std::cout << std::endl << "DELETING ALL ALLOCATIONS:" << std::endl;
    for (auto handle : handles) {
      // if (val.type == Value::STRING) {
      //   std::cout << '[' << *val.content.string.mem << "] ";
      //   std::cout << val.content.string.tail() << std::endl;
      // } else if (val.type == Value::VECTOR) {
      //   std::cout << *val.content.vector.mem << ' ';
      //   std::cout << val.content.vector.tail() << std::endl;
      // }
      switch (handle.type) {
        case Handle::CHAR:
          delete[] handle.object.char_ptr;
          break;
        case Handle::VALUE:
          delete[] handle.object.value_ptr;
          break;
        default:
          break; // don't forget the other types once they're implemented
      }
    }
  }

}