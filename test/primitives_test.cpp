#include "../src/context.hpp"
#include "../src/function.hpp"
#include "../src/primitives.hpp"
#include "../src/print.hpp"
#include <iostream>

using namespace std;
using namespace Vole;

int main() {
  auto ctx = Context();
  auto one = ctx.new_number(1);
  auto two = ctx.new_number(2);
  auto three = ctx.new_number(3);
  auto four = ctx.new_number(4);
  auto five = ctx.new_number(5);
  auto hey = ctx.new_symbol("hey");
  auto args = ctx.new_vector({ one, two, three, four, five });
  auto more = ctx.new_vector({ one, two, three, four, hey });
  auto sum = Primitives::add(ctx, args);
  cout << "sum: " << print(sum) << endl;

  try {
    auto bum = Primitives::add(ctx, more);
    cout << "bum: " << print(bum) << endl;
  } catch (const char* msg) {
    cout << msg << endl;
  }

  cout << "Is 'hey a number? " << print(Primitives::number_p(ctx, ctx.new_vector({ hey }))) << endl;

  return 0;
}

