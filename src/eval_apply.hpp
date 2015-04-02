#ifndef VOLE_EVAL_APPLY
#define VOLE_EVAL_APPLY


namespace Vole {

  class Context;
  class Env;
  struct Value;
  struct Function;
  template <typename T> struct Slice;
  using Vector = Slice<Value>;

  Value eval(Context& ctx, Value expr, Env& env);
  Value apply(Context& ctx, Function func, Vector args, Env& env);

}




#endif