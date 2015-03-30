#include <iostream>
#include "../src/hash.hpp"
#include "../src/symbol.hpp"
#include "../src/context.hpp"
#include "../src/eq.hpp"
#include "../src/env.hpp"
#include "../src/print.hpp"

using namespace Vole;
using namespace std;

int main() {
  auto ctx = Context();
  auto s1 = ctx.new_symbol("hello");
  auto s2 = ctx.new_symbol("hello");
  auto s3 = ctx.new_symbol("yo");
  auto s4 = ctx.new_gensym("hello");

  auto symhash = hash<Symbol>();

  cout << "hash(s1) = " << symhash(s1.content.symbol) << "." << endl;
  cout << "hash(s2) = " << symhash(s2.content.symbol) << "." << endl;
  cout << "hash(s3) = " << symhash(s3.content.symbol) << "." << endl;
  cout << "hash(s4) = " << symhash(s4.content.symbol) << "." << endl;

  cout << "s1 == s2: " << eq(s1.content.symbol, s2.content.symbol) << "." << endl;
  cout << "s2 == s3: " << eq(s2.content.symbol, s3.content.symbol) << "." << endl;
  cout << "s1 == s4: " << eq(s1.content.symbol, s4.content.symbol) << "." << endl;

  cout << "s1 == s2: " << (s1.content.symbol == s2.content.symbol) << "." << endl;
  cout << "s2 == s3: " << (s2.content.symbol == s3.content.symbol) << "." << endl;
  cout << "s1 == s4: " << (s1.content.symbol == s4.content.symbol) << "." << endl;

  auto outer = Env();
  auto inner = Env(&outer);
  
  auto xsym = ctx.new_symbol("x").content.symbol;
  outer.bind(xsym, ctx.new_number(1));
  auto val = inner.lookup(xsym);
  cout << "result of looking up 'x' in outer via inner (should be 1): " << print(val) << "." << endl;
  
  inner.bind(xsym, ctx.new_number(2));
  val = inner.lookup(xsym);
  cout << "result of looking up 'x' in inner (should be 2): " << print(val) << "." << endl;

  val = outer.lookup(xsym);
  cout << "result of looking up 'x' in outer (should be 1): " << print(val) << "." << endl;

  outer = Env();
  inner = Env(&outer);

  outer.bind(xsym, ctx.new_number(1));
  inner.assign(xsym, ctx.new_number(2));
  val = inner.lookup(xsym);
  cout << "result of looking up 'x' in inner (should be 2): " << print(val) << "." << endl;

  val = outer.lookup(xsym);
  cout << "result of looking up 'x' in outer (should be 2): " << print(val) << "." << endl;


  return 0;
}