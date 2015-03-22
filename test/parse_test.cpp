#include "../src/tokenize.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace Vole;

int main() {

  string src = "(def (factorial n) (if (= n 0) 1 (* n (factorial (- n 1)))))";
  vector<Lexeme> tokens;
  tokenize(src.c_str(), tokens);
  for (auto t : tokens) {
    switch (t.type) {
      case Lexeme::Type::LPAREN:
        cout << "LPAREN: ";
        break;
      case Lexeme::Type::RPAREN:
        cout << "RPAREN: ";
        break;
      case Lexeme::Type::IDENTIFIER:
        cout << "IDENTIFIER: ";
        break;
      case Lexeme::Type::NUMBER:
        cout << "NUMBER: ";
        break;
      case Lexeme::Type::BOOLEAN:
        cout << "BOOLEAN: ";
        break;
    }
    cout << string(t.beg, t.end) << endl;
  }

}

