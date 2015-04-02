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
        // ???
      break;

      // compound expressions
      case Value::VECTOR:
        // ???
      break;

      default:
        throw "unrecognized expression";
      break;
    }
  }

  Value eval_combination(Context& ctx, Vector expr, Env& env) {

  }

  Value apply(Context& ctx, Function func, Vector args) {

  }

}