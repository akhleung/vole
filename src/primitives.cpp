#include "primitives.hpp"
#include "context.hpp"
#include "value.hpp"

namespace Vole {
  namespace Primitives {

    using namespace std;

    bool number_p(Value arg) {
      return arg.type == Value::NUMBER;
    }

    Value number_p(Context& ctx, Value args) {
      return number_p(*args.content.vector.beg);
    }

    Value add(Context& ctx, Value args) {
      double sum = 0;
      for (Value arg : args.content.vector) {
        if (!number_p(arg)) {
          throw "arguments to `+` must be numbers";
        }
        sum += arg.content.number;
      }
      return ctx.new_number(sum);
    }

  }
}
