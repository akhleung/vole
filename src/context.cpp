#include "context.hpp"
#include "function.hpp"
#include "primitives.hpp"
#include <algorithm>

namespace Vole {

  using namespace std;
  using namespace Primitives;

  Context::Context()
  : allocator(Allocator()),
    symbol_table(Symbol_Table()),
    global_environment(Env(nullptr)) {

    bind_primitive("boolean?", boolean_p);
    bind_primitive("number?", number_p);
    bind_primitive("symbol?", symbol_p);
    bind_primitive("string?", string_p);
    bind_primitive("vector?", vector_p);
    bind_primitive("function?", function_p);
    bind_primitive("+", add);
    bind_primitive("-", sub);
    bind_primitive("*", mul);
    bind_primitive("/", div);
    bind_primitive("length", length);
    bind_primitive("map", map);
    bind_primitive("filter", filter);

  }

  void Context::bind_primitive(const char* name, Primitive prim) {
    auto name_sym = new_symbol(name).content.symbol;
    global_environment.bind(name_sym, Value(Function(prim)));
  }

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
    auto mem = allocator.alloc_values(cap);
    return Value(Vector(mem, mem, 0, cap));
  }

  Value Context::new_vector(const initializer_list<Value>& lst) {
    return Value(Vector(allocator, lst));
  }

  Value Context::new_vector(const vector<Value>& vec) {
    return Value(Vector(allocator, vec));
  }

}