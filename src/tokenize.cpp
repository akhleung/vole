#include "tokenize.hpp"

namespace Vole {

  using namespace Munchar;
  using namespace Munchar::Tokens;

  void tokenize(const char* src, vector<Lexeme>& tokens) {
    const char* munched;
    while (*src) {
      if (munched = left_paren(src)) {
        tokens.push_back(Lexeme(Lexeme::Type::LPAREN, src, munched));
        src = munched+1;
      } else if (munched = right_paren(src)) {
        tokens.push_back(Lexeme(Lexeme::Type::RPAREN, src, munched));
        src = munched+1;
      } else if (munched = number(src)) {
        tokens.push_back(Lexeme(Lexeme::Type::NUMBER, src, munched));
        src = munched+1;
      } else if (munched = lisp_true(src)) {
        tokens.push_back(Lexeme(Lexeme::Type::BOOLEAN, src, munched));
        src = munched+1;
      } else if (munched = lisp_false(src)) {
        tokens.push_back(Lexeme(Lexeme::Type::BOOLEAN, src, munched));
        src = munched+1;
      } else if (munched = lisp_identifier(src)) {
        tokens.push_back(Lexeme(Lexeme::Type::IDENTIFIER, src, munched));
        src = munched+1;
      } else {

      }
    }
  }

}