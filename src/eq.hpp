#ifndef VOLE_EQ
#define VOLE_EQ

#include "value.hpp"

namespace Vole {

  bool eq(const Value l, const Value r);

  // provide declarations for eq on symbols and slices
  bool operator==(const Symbol l, const Symbol r);

  bool eq(const Symbol l, const Symbol r);

  template <typename T>
  bool eq(const Slice<T> l, const Slice<T> r) {
    return ((l.beg == r.beg) && (l.len == r.len));
  }

}

#endif