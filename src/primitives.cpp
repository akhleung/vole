#include "primitives.hpp"
#include "context.hpp"
#include "value.hpp"
#include "append.hpp"

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

    Value sub(Context& ctx, Vector args) {
      if (args.len < 1) {
        throw "at least one argument required to `-`";
      }
      if (args.len == 1) {
        return ctx.new_number(0 - args[0].content.number);
      }
      double diff = args[0].content.number;
      for (Value arg : args) {
        if (!number_p(arg)) {
          throw "arguments to `-` must be numbers";
        }
        diff -= arg.content.number;
      }
      return ctx.new_number(diff);
    }

    Value mul(Context& ctx, Vector args) {
      double prod = 1;
      for (Value arg : args) {
        if (!number_p(arg)) {
          throw "arguments to `*` must be numbers";
        }
        prod *= arg.content.number;
      }
      return ctx.new_number(prod);
    }

    Value div(Context& ctx, Vector args) {
      if (args.len < 1) {
        throw "at least one argument required to `/`";
      }
      if (args.len == 1) {
        return ctx.new_number(1 / args[0].content.number);
      }
      double divis = args[0].content.number;
      for (Value arg : args) {
        if (!number_p(arg)) {
          throw "arguments to `-` must be numbers";
        }
        if (arg.content.number == 0) {
          throw "cannot divide by 0";
        }
        divis /= arg.content.number;
      }
      return ctx.new_number(divis);
    }

    Value map(Context& ctx, Vector args) {
      auto f = args[0];
      auto list = args[1];
      if (f.type != Value::FUNCTION) {
        throw "first argument to map must be a function";
      }
      if (list.type != Value::VECTOR) {
       throw "second argument to map must be a vector"; 
      }
      auto results = ctx.new_vector(list.content.vector.len);
      for (Value item : list.content.vector) {
        Value argbuffer[1] = { item };
        Vector fargs = Vector(argbuffer, 1);
        results.content.vector = append(ctx.allocator, results.content.vector, f.content.function(ctx, fargs));
      }
      return results;
    }

    Value filter(Context& ctx, Vector args) {
      auto f = args[0];
      auto list = args[1];
      if (f.type != Value::FUNCTION) {
        throw "first argument to filter must be a function";
      }
      if (list.type != Value::VECTOR) {
       throw "second argument to filter must be a vector"; 
      }
      auto results = ctx.new_vector(list.content.vector.len);
      for (Value item : list.content.vector) {
        Value argbuffer[1] = { item };
        Vector fargs = Vector(argbuffer, 1);
        if (f.content.function(ctx, fargs).content.boolean == true) {
          results.content.vector = append(ctx.allocator, results.content.vector, item);
        }
      }
      return results;
    }

  }
}
