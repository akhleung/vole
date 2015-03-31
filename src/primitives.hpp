#ifndef VOLE_PRIMITIVES
#define VOLE_PRIMITIVES

namespace Vole {
  class Context;
  struct Value;
  namespace Primitives {
    
    Value number_p(Context& ctx, Value args);
    Value add(Context& ctx, Value args);

  }
}

#endif