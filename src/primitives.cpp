#include "primitives.hpp"
#include "context.hpp"
#include "value.hpp"

namespace Vole {
  namespace Primitives {

    using namespace std;

    bool number_p(Value arg) {
      return arg.type == Value::NUMBER;
    }

    Value number_p(Context& ctx, Vector args) {
      return number_p(*args.begin());
    }

    bool bool_p(Value arg) {
      return arg.type == Value::BOOLEAN;
    }

    Value bool_p(Context& ctx, Vector args) {
      return bool_p(*args.begin());
    }

    bool symbol_p(Value arg) {
      return arg.type == Value::SYMBOL;
    }

    Value symbol_p(Context& ctx, Vector args) {
      return symbol_p(*args.begin());
    }

    bool string_p(Value arg) {
      return arg.type == Value::STRING;
    }

    Value string_p(Context& ctx, Vector args) {
      return string_p(*args.begin());
    }

    bool vector_p(Value arg) {
      return arg.type == Value::VECTOR;
    }

    Value vector_p(Context& ctx, Vector args) {
      return vector_p(*args.begin());
    }

    bool function_p(Value arg) {
      return arg.type == Value::FUNCTION;
    }

    Value function_p(Context& ctx, Vector args) {
      return function_p(*args.begin());
    }

    Value add(Context& ctx, Vector args) {
      double sum = 0;
      for (Value arg : args) {
        if (!number_p(arg)) {
          throw "arguments to `+` must be numbers";
        }
        sum += arg.content.number;
      }
      return ctx.new_number(sum);
    }

    // Value sub(Context& ctx, Vector args) {
    //   double diff = 0;
    //   for (Value arg : args) {
    //     if (!number_p(arg)) {
    //       throw "arguments to `+` must be numbers";
    //     }
    //     diff += arg.content.number;
    //   }
    //   return ctx.new_number(sum);
    // }

  }
}
