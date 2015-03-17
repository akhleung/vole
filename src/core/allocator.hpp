#ifndef VOLE_ALLOCATOR
#define VOLE_ALLOCATOR

#include <utility>
#include <forward_list>

namespace Vole {

  struct Value;

  class Allocator {

    struct Handle {
      enum Type {
        CHAR, VALUE
      } type;
      union Object {
        char* char_ptr;
        Value* value_ptr;
        Object(char*);
        Object(Value*);
      } object;
      Handle(Type t, char* ptr);
      Handle(Type t, Value* ptr);
    };

    std::forward_list<Handle> handles;

  public:

    char*  alloc_string(size_t size, char color = 'w');
    Value* alloc_vector(size_t size, char color = 'w');
    ~Allocator();

  };

}

#endif
