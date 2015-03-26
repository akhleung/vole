#include "tokenize.hpp"
#include "munchar_tokens.hpp"

namespace Vole {

  using namespace std;
  using namespace Munchar;
  using namespace Munchar::Tokens;

  Lexeme::Lexeme(
    Type t,
    const string& txt,
    size_t ln
  )
  : type(t), text(txt), line(ln)
  { }

  void tokenize(
    const char* src,
    size_t line,
    vector<Lexeme>& tokens
  ) {
    const char* munched;
    while (*src) {
      switch (*src) {
        case '\n':
          munched = src+1;
          ++line;
        break;

        case '\t':
        case '\r':
        case ' ':
          munched = spaces(src);
        break;

        case '"':
          if ((munched = lisp_string(src))) {
            tokens.push_back(
              Lexeme(Lexeme::STRING, string(src, munched), line)
            );
          } else {
            // unterminated string
            tokens.push_back(
              Lexeme(Lexeme::ERROR, string(src, munched), line)
            );
          }
        break;

        case '#':
          if ((munched = lisp_boolean(src))) {
            tokens.push_back(
              Lexeme(Lexeme::BOOLEAN, string(src, munched), line)
            );
          } else {
            // unrecognized hash-thingy
            tokens.push_back(
              Lexeme(Lexeme::ERROR, string(src, munched), line)
            );
          }
        break;

        case '\'':
          tokens.push_back(
            Lexeme(Lexeme::QUOTE, string(src, (munched = src+1)), line)
          );
        break;

        case '(':
          tokens.push_back(
            Lexeme(Lexeme::LPAREN, string(src, (munched = src+1)), line)
          );
        break;

        case ')':
          tokens.push_back(
            Lexeme(Lexeme::RPAREN, string(src, (munched = src+1)), line)
          );
        break;

        case ';':
          munched = lisp_comment(src);
          ++line;
        break;

        default:
          if ((munched = number(src))) {
            tokens.push_back(
              Lexeme(Lexeme::NUMBER, string(src, munched), line)
            );
          } else if ((munched = lisp_identifier(src))) {
            tokens.push_back(
              Lexeme(Lexeme::IDENTIFIER, string(src, munched), line)
            );
          } else {
            // unrecognized thing in general
            tokens.push_back(
              Lexeme(Lexeme::ERROR, string(src, munched), line)
            );
          }
        break;
      }
      src = munched;
    }
    tokens.push_back(
      Lexeme(Lexeme::EOI, string(src, munched), line)
    );
  }

}