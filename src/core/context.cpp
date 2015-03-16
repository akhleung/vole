#include "context.hpp"

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

  Value Context::new_symbol(string name) {
    return Value(symbol_table.intern(allocator, name));
  }

  Value Context::new_string(string str) {
    return Value(String(allocator, str));
  }

  Value Context::new_vector(size_t cap) {
    return Value(Vector(allocator, 0, cap));
  }

}