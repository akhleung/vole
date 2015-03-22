#ifndef VOLE_TOKENIZE
#define VOLE_TOKENIZE

#include <vector>

namespace Vole {

  struct Lexeme {
    enum Type {
      LPAREN,
      RPAREN,
      IDENTIFIER,
      NUMBER,
      BOOLEAN
    } type;
    const char* beg;
    const char* end;
    Lexeme(Type t, const char* b, const char* e) : type(t), beg(b), end(e) { }
  };

  void tokenize(const char* src, std::vector<Lexeme>& tokens);

}

#endif