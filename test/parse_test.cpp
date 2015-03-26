#include "../src/tokenize.hpp"
#include "../src/parser.hpp"
#include "../src/print.hpp"
#include "../src/context.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace Vole;

int main() {

  string src = "(def (factorial n) (if (= n 0) 1 (* n (factorial (- n 1)))))";
  vector<Lexeme> tokens;
  tokenize(src.c_str(), 1, tokens);
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
      case Lexeme::Type::STRING:
        cout << "STRING: ";
        break;
      case Lexeme::Type::QUOTE:
        cout << "QUOTE: ";
        break;
      default:
        cout << "WHAT? ";
        break;
    }
    cout << t.text << endl;
  }

  auto c = Context();
  auto p = Parser("(hello (one two (three) ) )", c);
  Value result = p.parse();
  cout << print(result) << endl;

  auto p2 = Parser("(+ 1 2.34 -0.3 (* #f blah) ((fudge) #t) \"hello\")", c);
  Value r2 = p2.parse();
  cout << print(r2) << endl;

}

