#ifndef VOLE_CONTEXT
#define VOLE_CONTEXT

#include "allocator.hpp"
#include "symbol.hpp"
#include "value.hpp"
#include <string>
#include <vector>

namespace Vole {

  class Context {
  public:
    Context();
    Value new_boolean(bool b);
    Value new_number(double d);
    Value new_symbol(const std::string& name);
    Value new_gensym(const std::string& name);
    Value new_string(const std::string& str);
    Value new_vector(size_t cap);
    Value new_vector(const std::initializer_list<Value>& lst);
    Value new_vector(const std::vector<Value>& vec);
  private:
    Allocator allocator;
    Symbol_Table symbol_table;
  };

}

#endif