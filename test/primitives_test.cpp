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
  auto negfive = ctx.new_number(-5);
  auto hey = ctx.new_symbol("hey");
  auto ho = ctx.new_symbol("ho");
  auto args = ctx.new_vector({ one, two, three, four, five });
  auto argsone = ctx.new_vector({ five });
  auto argsneg = ctx.new_vector({ negfive });
  auto more = ctx.new_vector({ one, hey, three, ho, five });
  auto sum = Primitives::add(ctx, args.content.vector);
  cout << "sum: " << print(sum) << endl;
  auto diff = Primitives::sub(ctx, args.content.vector);
  cout << "diff: " << print(diff) << endl;
  auto diffone = Primitives::sub(ctx, argsone.content.vector);
  cout << "diff one arg: " << print(diffone) << endl;
  auto diffneg = Primitives::sub(ctx, argsneg.content.vector);
  cout << "diff negative arg: " << print(diffneg) << endl;
  auto prod = Primitives::mul(ctx, args.content.vector);
  cout << "mul: " << print(prod) << endl;
  auto divis = Primitives::div(ctx, args.content.vector);
  cout << "divis: " << print(divis) << endl;
  auto divisone = Primitives::div(ctx, argsone.content.vector);
  cout << "divis one arg: " << print(divisone) << endl;
  auto divisneg = Primitives::div(ctx, argsneg.content.vector);
  cout << "divis negative arg: " << print(divisneg) << endl;

  try {
    auto bum = Primitives::add(ctx, more.content.vector);
    cout << "bum: " << print(bum) << endl;
  } catch (const char* msg) {
    cout << msg << endl;
  }

  cout << "Is 'hey a number? " << print(Primitives::number_p(ctx, ctx.new_vector({ hey }).content.vector)) << endl;

  auto nump = Function(Primitives::number_p);
  cout << "(map number? '(1 hey 3 ho 5)) => " << print(Primitives::map(ctx, ctx.new_vector({nump, more}).content.vector)) << endl;
  cout << "(filter number? '(1 hey 3 ho 5)) => " << print(Primitives::filter(ctx, ctx.new_vector({nump, more}).content.vector)) << endl;

  cout << "(length '(1 hey 3 ho 5)) => " << print(Primitives::length(ctx, ctx.new_vector({ more }).content.vector)) << endl;
  cout << "(length \"hello\") => " << print(Primitives::length(ctx, ctx.new_vector({ ctx.new_string("hello") }).content.vector)) << endl;

  cout << "printing out `number?`: " << print(nump) << endl;
  return 0;
}

