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
        return env.lookup(expr);
      break;

      // compound expressions
      case Value::VECTOR:
        return eval_combination(ctx, expr.content.vector, env)
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
        results = append(ctx.allocator, results, eval(ctx, expr[i], env));
      }
      if (results.head().type != Value::FUNCTION) {
        throw "first argument is not a function";
      }
      return apply(ctx, results.head().content.function, results.tail());
    }

    // switch (id.type) {
    //   case Value::SYMBOL:
    //     if (id == quote) {
    //       return expr[1];
    //     }

    //   break;
    //  default:
    //    Value results = ctx.new_vector(expr.len);
    //    for (int i = 0; i < expr.len; ++i) {
    //      results.append(eval(ctx, expr[i], env));
    //    }
    //    if (results[0].type != Value::FUNCTION) {
    //      throw "first argument is not a function";
    //    }
    //    return apply(ctx, results[0], results[1]);
    //  break;
    // }
  }

  Value apply(Context& ctx, Function func, Vector args) {
    return func(ctx, args);
  }

}