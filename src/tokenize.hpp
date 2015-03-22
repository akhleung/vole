#ifndef VOLE_TOKENIZE
#define VOLE_TOKENIZE

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

  vector<Lexeme>& tokenize(const char* src, vector<Lexeme>& tokens);

}

#endif