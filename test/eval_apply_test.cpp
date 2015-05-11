#include "../src/eval_apply.hpp"
#include "../src/parser.hpp"
#include "../src/print.hpp"
#include "../src/context.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace Vole;

int main() {

  try {
      auto c = Context();
      auto add = "(+ 1 2)";
      auto p = Parser(add, c);
      Value r = p.parse();
      try {
        Value eval_result = eval(c, r, c.global_environment);
        cout << add << " evals to " << print(eval_result) << endl;
      }
      catch (const char* msg) {
        cout << msg << endl;
      }

      auto boolean = "(boolean? 8)";
      Value b = Parser(boolean, c).parse();
      Value bool_result = eval(c, b, c.global_environment);
      cout << boolean << " evals to " << print(bool_result) << endl;


      auto func = "(function? *)";
      Value f = Parser(func, c).parse();
      Value func_result = eval(c, f, c.global_environment);
      cout << func << " evals to " << print(func_result) << endl;

      auto length = "(length '(1 2 3 4 5))";
      Value l = Parser(length, c).parse();
      try {
        Value length_result = eval(c, l, c.global_environment);
        cout << length << " evals to " << print(length_result) << endl;
      }
      catch (const char* msg) {
        cout << msg << endl;
      }

      auto map = "(map number? '(3 (9 3) true + 3 5))";
      Value m = Parser(map, c).parse();
      try {
        Value map_result = eval(c, m, c.global_environment);
        cout << map << " evals to " << print(map_result) << endl;
      }
      catch (const char* msg) {
        cout << msg << endl;
      }

      auto filter = "(filter string? '(#f 8 \"eight\" (1 2) \"hello\"))";
      Value filt = Parser(filter, c).parse();
      try {
        Value filter_result = eval(c, filt, c.global_environment);
        cout << filter << " evals to " << print(filter_result) << endl;
      }
      catch (const char* msg) {
        cout << msg << endl;
      }
  } 
  catch (const char* msg) {
    cout << msg << endl;
  }

  return 0;
}



