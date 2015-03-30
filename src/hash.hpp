#ifndef VOLE_HASH
#define VOLE_HASH

#include "value.hpp"
#include <functional>

namespace std {

  template <>
  struct hash<Vole::Symbol> {
    size_t operator()(Vole::Symbol sym) const;
  };

}

#endif