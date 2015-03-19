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

  Value Context::new_string(const string& str) {
    auto len = str.length();
    auto mem = allocator.alloc_string(len);
    std::copy(str.begin(), str.end(), mem);
    return Value(String(mem, mem, len, len));
  }

  Value Context::new_vector(size_t cap) {
    auto mem = allocator.alloc_vector(cap);
    return Value(Vector(mem, mem, 0, cap));
  }

  Value Context::new_vector(const initializer_list<Value>& lst) {
    auto cap = lst.size();
    auto mem = allocator.alloc_vector(cap);
    std::copy(lst.begin(), lst.end(), mem);
    return Value(Vector(mem, mem, cap, cap));
  }

  Value Context::new_vector(const vector<Value>& vec) {
    auto cap = vec.size();
    auto mem = allocator.alloc_vector(cap);
    std::copy(vec.begin(), vec.end(), mem);
    return Value(Vector(mem, mem, cap, cap));
  }

}