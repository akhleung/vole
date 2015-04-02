#include "../src/tokenize.hpp"
#include "../src/parser.hpp"
#include "../src/print.hpp"
#include "../src/context.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace Vole;

int main() {

  string src = "(def (factorial n) (if (= n 0) 'boop (* n (factorial (- n 1)))))";
  vector<Lexeme> tokens;
  tokenize(src.c_str(), tokens, 1);
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

  auto p2 = Parser("(+ 1 2.34 -0.3 '(doot (doot doot)) ''double-quoted (* #f blah) ((fudge) #t) '#f \"hello\")", c);
  Value r2 = p2.parse();
  cout << print(r2) << endl;

  auto fact_def
    = R"(
    ; everyone's favorite introductory recursive function
    (define (factorial n)
      (if (= n 0)
          1
          (* n (factorial (- n 1)))))
    )";
  auto p3 = Parser(fact_def, c);
  Value r3 = p3.parse();
  cout << print(r3) << endl;

  auto expr_comment
    = R"(
    (blah blah #; (this should not be here) etc)
    )";
  auto p4 = Parser(expr_comment, c);
  Value r4 = p4.parse();
  cout << print(r4) << endl;

  auto unmatched_paren = ") a b c";
  auto p5 = Parser(unmatched_paren, c);
  try {
    Value r5 = p5.parse();
    cout << print(r5) << endl;
  }
  catch (const char* msg) {
    cout << msg << endl;
  }

  auto unterminated_expr = "(a b c";
  auto p6 = Parser(unterminated_expr, c);
  try {
    Value r6 = p6.parse();
    cout << print(r6) << endl;
  }
  catch (const char* msg) {
    cout << msg << endl;
  }

}

