#ifndef VOLE_CONTEXT
#define VOLE_CONTEXT

#include "allocator.hpp"
#include "symbol.hpp"
#include "value.hpp"
#include <string>

namespace Vole {

  class Context {
  public:
    Context();
    Value new_boolean(bool b);
    Value new_number(double d);
    Value new_symbol(std::string name);
    Value new_string(std::string str);
    Value new_vector(size_t cap);
  private:
    Allocator allocator;
    Symbol_Table symbol_table;
  };

}

#endif