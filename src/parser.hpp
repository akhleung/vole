#ifndef VOLE_PARSER
#define VOLE_PARSER

#include "context.hpp"
#include "tokenize.hpp"
#include "value.hpp"
#include <vector>

namespace Vole {

  class Parser {
    char* src;
    Context& ctx;
    std::vector<Lexeme> tokens;
    size_t index;

  public:
    Parser(char* s, Context& c);
    Value parse();
    Value parse_value();
    Value parse_vector();
  };

}

#endif