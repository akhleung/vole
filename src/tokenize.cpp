#include "tokenize.hpp"
#include "munchar_tokens.hpp"

namespace Vole {

  using namespace std;
  using namespace Munchar;

  Lexeme::Lexeme(Type t, const string& txt, size_t ln)
  : type(t), text(txt), line(ln)
  { }

  void tokenize(const char* src, vector<Lexeme>& tokens, size_t line) {
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
          munched = Tokens::spaces(src);
        break;

        case '"':
          if ((munched = Tokens::string(src))) {
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
          if ((munched = Tokens::boolean(src))) {
            tokens.push_back(
              Lexeme(Lexeme::BOOLEAN, string(src, munched), line)
            );
          } else if ((munched = Tokens::hash_comment(src))) {
            tokens.push_back(
              Lexeme(Lexeme::COMMENT, string(src, munched), line)
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
          munched = Tokens::line_comment(src);
          ++line;
        break;

        default:
          if ((munched = Tokens::number(src))) {
            tokens.push_back(
              Lexeme(Lexeme::NUMBER, string(src, munched), line)
            );
          } else if ((munched = Tokens::identifier(src))) {
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