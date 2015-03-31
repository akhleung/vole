#include "function.hpp"
#include "context.hpp"
#include "value.hpp"

namespace Vole {

  Function::Function(Primitive p) : primitive(p) { }

  Value Function::operator()(Context& ctx, Value args) {
    return primitive(ctx, args);
  }

}