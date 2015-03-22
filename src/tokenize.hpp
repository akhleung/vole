#ifndef VOLE_TOKENIZE
#define VOLE_TOKENIZE

#include <cctype>

namespace Vole {

  #include "munchar.hpp"
  #include "munchar_tokens.hpp"

  namespace Munchar {
    namespace Tokens {
      // more tokens
    }
  }

  const char* munch(const char* src);

}

#endif