#ifndef VOLE_PRINT
#define VOLE_PRINT

#include "value.hpp"
#include <string>

namespace Vole {

  std::string print(String str);
  std::string print(Vector vec);
  std::string print(Symbol sym);
  std::string print(Value val);

}

#endif