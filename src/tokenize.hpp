#ifndef VOLE_TOKENIZE
#define VOLE_TOKENIZE

#include <cctype>

namespace Vole {

  #include "munchar.hpp"
  #include "munchar_tokens.hpp"

  namespace Munchar {
    namespace Tokens {
      // more tokens
      constexpr auto lisp_true          = STR("#t");
      constexpr auto lisp_false         = STR("#f");
      constexpr auto lisp_id_start      = letter | underscore | hyphen;
      constexpr auto lisp_id_body       = alphanumeric | underscore | hyphen;
      constexpr auto lisp_identifier    = lisp_id_start^*lisp_id_body;
    }
  }

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

  vector<Lexeme>& tokenize(const char* src, vector<Lexeme>& tokens);

}

#endif