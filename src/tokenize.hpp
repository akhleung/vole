#ifndef VOLE_TOKENIZE
#define VOLE_TOKENIZE

#include <vector>
#include <string>

namespace Vole {

  struct Lexeme {
    enum Type {
      LPAREN,
      RPAREN,
      IDENTIFIER,
      NUMBER,
      BOOLEAN,
      STRING,
      QUOTE,
      EOI,
      ERROR
    } type;
    std::string text;
    size_t line;
    Lexeme(Type t, const std::string& txt, size_t ln);
  };

  void tokenize(const char* src, std::vector<Lexeme>& token, size_t line);

}

#endif