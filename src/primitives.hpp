#ifndef VOLE_PRIMITIVES
#define VOLE_PRIMITIVES

namespace Vole {
  class Context;
  struct Value;
  template <typename T> struct Slice;
  using Vector = Slice<Value>;
  
  namespace Primitives {
    
    Value number_p(Context& ctx, Vector args);
    Value add(Context& ctx, Vector args);

  }
}

#endif