#ifndef VOLE_FUNCTION
#define VOLE_FUNCTION

namespace Vole {

  class Context;
  struct Value;
  // template <typename T> struct Slice;
  // using Vector = Slice<Value>;

  using Primitive = Value (*)(Context&, Value);

  struct Function {
    Primitive primitive;

    Function(Primitive p);
    Value operator()(Context& ctx, Value args);
  };

}

#endif