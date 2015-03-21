#include "context.hpp"
#include <algorithm>

namespace Vole {

  using namespace std;

  Context::Context()
  : allocator(Allocator()), symbol_table(Symbol_Table())
  { }

  Value Context::new_boolean(bool b) {
    return Value(b);
  }

  Value Context::new_number(double d) {
    return Value(d);
  }

  Value Context::new_symbol(const string& name) {
    return Value(symbol_table.intern(allocator, name));
  }

  Value Context::new_gensym(const string& name) {
    return Value(Symbol(String(allocator, name)));
  }

  Value Context::new_string(const string& str) {
    return Value(String(allocator, str));
  }

  Value Context::new_vector(size_t cap) {
    auto mem = allocator.alloc_vector(cap);
    return Value(Vector(mem, mem, 0, cap));
  }

  Value Context::new_vector(const initializer_list<Value>& lst) {
    return Value(Vector(allocator, lst));
  }

  Value Context::new_vector(const vector<Value>& vec) {
    return Value(Vector(allocator, vec));
  }

}