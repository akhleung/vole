#include "append.hpp"
#include "eval_apply.hpp"
#include "context.hpp"
#include "env.hpp"
#include "value.hpp"
#include "function.hpp"

namespace Vole {

  static Value eval_combination(Context& ctx, Vector expr, Env& env);

  Value eval(Context& ctx, Value expr, Env& env) {
    switch (expr.type) {
      // atomic expressions
      case Value::BOOLEAN:
      case Value::NUMBER:
      case Value::STRING:
      case Value::FUNCTION:
        return expr;
      break;

      case Value::SYMBOL:
        return env.lookup(expr.content.symbol);
      break;

      // compound expressions
      case Value::VECTOR:
        return eval_combination(ctx, expr.content.vector, env);
      break;

      default:
        throw "unrecognized expression";
      break;
    }
  }

  Value eval_combination(Context& ctx, Vector expr, Env& env) {
    Value id = expr.head();
    Value quote = ctx.new_symbol("quote");
    if (id.type == Value::SYMBOL && eq(id, quote)) {
      return expr[1];
    } else {
      Value results = ctx.new_vector(expr.len);
      for (int i = 0; i < expr.len; ++i) {
        results = append(ctx.allocator, results.content.vector, eval(ctx, expr[i], env));
      }
      if (results.content.vector.head().type != Value::FUNCTION) {
        throw "first argument is not a function";
      }
      return apply(ctx, results.content.vector.head().content.function, results.content.vector.tail());
    }
  }

  Value apply(Context& ctx, Function func, Vector args) {
    return func(ctx, args);
  }

}