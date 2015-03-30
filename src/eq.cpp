#include "eq.hpp"

namespace Vole {

  bool eq(const Value l, const Value r) {
    if (l.type == r.type) {
      switch (l.type) {
        case Value::BOOLEAN: return    l.content.boolean == r.content.boolean;
        case Value::NUMBER:  return    l.content.number  == r.content.number;
        case Value::SYMBOL:  return eq(l.content.symbol,    r.content.symbol);
        case Value::STRING:  return eq(l.content.string,    r.content.string);
        case Value::VECTOR:  return eq(l.content.vector,    r.content.vector);
        case Value::COLOR:   return    l.content.color   == r.content.color;
        default:             return false;
      }
    } else {
      return false;
    }
  }

  // provide definitions for eq on symbols and slices

  bool operator==(const Symbol l, const Symbol r) {
    return eq(l, r);
  }

  bool eq(const Symbol l, const Symbol r) {
    return (l.name.beg == r.name.beg);
  }

}