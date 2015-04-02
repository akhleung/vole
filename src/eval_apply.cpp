#include "eval_apply.hpp"
#include "context.hpp"
#include "env.hpp"
#include "value.hpp"
#include "function.hpp"

namespace Vole {

  Value eval(Context& ctx, Value expr, Env& env) {
    switch (expr.type) {
      case Value::BOOLEAN:
      case Value::NUMBER:
      case Value::STRING:
      case Value::FUNCTION:
        return expr;
      break;

      case Value::SYMBOL:
        // ???
      break;

      case Value::VECTOR:
        // ???
      break;

      default:
        throw "unrecognized expression";
      break;
    }
  }

  Value apply(Context& ctx, Function func, Vector args, Env& env) {

  }

}