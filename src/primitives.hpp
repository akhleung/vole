#ifndef VOLE_PRIMITIVES
#define VOLE_PRIMITIVES

namespace Vole {
  class Context;
  struct Value;
  template <typename T> struct Slice;
  using Vector = Slice<Value>;
  
  namespace Primitives {
    
    Value boolean_p(Context& ctx, Vector args);
    Value number_p(Context& ctx, Vector args);
    Value symbol_p(Context& ctx, Vector args);
    Value string_p(Context& ctx, Vector args);
    Value vector_p(Context& ctx, Vector args);
    Value function_p(Context& ctx, Vector args);
    Value add(Context& ctx, Vector args);
    Value sub(Context& ctx, Vector args);
    Value mul(Context& ctx, Vector args);
    Value div(Context& ctx, Vector args);
    Value length(Context& ctx, Vector args);
    Value map(Context& ctx, Vector args);
    Value filter(Context& ctx, Vector args);

  }
}

#endif