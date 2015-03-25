#include "tokenize.hpp"
#include "munchar_tokens.hpp"

namespace Vole {

  using namespace Munchar;
  using namespace Munchar::Tokens;

  Lexeme::Lexeme(Type t, const char* b, const char* e)
  : type(t), beg(b), end(e) 
  { }

  void tokenize(const char* src, std::vector<Lexeme>& tokens) {
    const char* munched;
    while (*src) {
      if ((munched = left_paren(src))) {
        tokens.push_back(Lexeme(Lexeme::Type::LPAREN, src, munched));
        src = munched;
      } else if ((munched = right_paren(src))) {
        tokens.push_back(Lexeme(Lexeme::Type::RPAREN, src, munched));
        src = munched;
      } else if ((munched = number(src))) {
        tokens.push_back(Lexeme(Lexeme::Type::NUMBER, src, munched));
        src = munched;
      } else if ((munched = boolean(src))) {
        tokens.push_back(Lexeme(Lexeme::Type::BOOLEAN, src, munched));
        src = munched;
      } else if ((munched = lisp_identifier(src))) {
        tokens.push_back(Lexeme(Lexeme::Type::IDENTIFIER, src, munched));
        src = munched;
      } else if ((munched = whitespace(src))) {
        src = munched;
      } else {
        // TODO: replace with our own error object
        throw "unrecognized token";
      }
    }
  }

}