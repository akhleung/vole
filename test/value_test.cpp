#include "../src/context.hpp"
#include "../src/print.hpp"
#include <iostream>
#include <functional>

using namespace std;
using namespace Vole;

int main() {
  auto ctx = Context();

  auto hello = ctx.new_string("hello");
  auto world = ctx.new_string("world");
  vector<Value> vec = { hello, world };
  auto greet = ctx.new_vector(vec);

  cout << print(greet) << endl;

  auto pi = ctx.new_number(3.14);
  auto me = ctx.new_string("Aaron");
  auto tr = ctx.new_boolean(true);
  auto lst = { pi, me, greet, tr };
  auto stuff = ctx.new_vector(lst);

  cout << print(stuff) << endl;

  // (def (square x) (* x x))
  auto def = ctx.new_symbol("def");
  auto square = ctx.new_symbol("square");
  auto x = ctx.new_symbol("x");
  auto mul = ctx.new_symbol("*");

  auto sig = ctx.new_vector({ square, x });
  auto body = ctx.new_vector({ mul, x, x });
  auto square_def = ctx.new_vector({ def, sig, body });

  cout << print(square_def) << endl;

  // (def (factorial n)
  //   (if (= n 0)
  //       1
  //       (* n (factorial (- n 1)))))
  // auto factorial = Value(String(alloc, "factorial"));
  auto factorial = ctx.new_symbol("factorial");
  auto n = ctx.new_symbol("n");
  auto iff = ctx.new_symbol("if");
  auto equal = ctx.new_symbol("=");
  auto zero = ctx.new_number(0);
  auto one = ctx.new_number(1);
  auto minus = ctx.new_symbol("-");

  auto fact_sig = ctx.new_vector({ factorial, n });
  auto cond = ctx.new_vector({ equal, n, zero });
  auto args = ctx.new_vector({ minus, n, one });
  auto recur = ctx.new_vector({ factorial, args });
  auto alt = ctx.new_vector({ mul, n, recur });
  auto fact_body = ctx.new_vector({ iff, cond, one, alt });
  auto fact_def = ctx.new_vector({ def, fact_sig, fact_body });

  cout << print(fact_def) << endl;

}

