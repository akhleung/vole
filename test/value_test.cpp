#include "../src/slice.hpp"
#include "../src/value.hpp"
#include "../src/allocator.hpp"
#include <iostream>
#include <functional>

using namespace std;
using namespace Vole;

int main() {
  auto alloc = Allocator();
  auto strval = Value(slice_from_string(alloc, "a string slice"));
  cout << "fetching out the slice: " << string(strval.content.string) << endl;
  cout << "outputting directly: " << strval << endl;
  auto serialized = string(strval);
  cout << "serialized: " << serialized << endl;

  auto thing1 = Value(String(alloc, "hey"));
  auto thing2 = Value(3.14);
  auto thing3 = Value(String(alloc, "hoo"));
  auto things = Value(Vector(alloc, { thing1, thing2, thing3 }));
  cout << "things: " << things << endl;

  auto boolval = Value(true);
  auto numval = Value(2.78);
  strval = Value(String(alloc, "a string"));
  auto values = Value(Vector(alloc, { boolval, numval, strval }));
  cout << "values: " << values << endl;

  // (def (square x) (* x x))
  auto def = Value(String(alloc, "def"));
  auto square = Value(String(alloc, "square"));
  auto x = Value(String(alloc, "x"));
  auto mul = Value(String(alloc, "*"));

  auto sig = Value(Vector(alloc, { square, x }));
  auto body = Value(Vector(alloc, { mul, x, x }));
  auto square_def = Value(Vector(alloc, { def, sig, body }));

  cout << square_def << endl;

  // (def (factorial n)
  //   (if (= n 0)
  //       1
  //       (* n (factorial (- n 1)))))
  auto factorial = Value(String(alloc, "factorial"));
  auto n = Value(String(alloc, "n"));
  auto iff = Value(String(alloc, "if"));
  auto equal = Value(String(alloc, "="));
  auto zero = Value(0);
  auto one = Value(1);
  auto minus = Value(String(alloc, "-"));

  auto fact_sig = Value(Vector(alloc, { factorial, n }));
  auto cond = Value(Vector(alloc, { equal, n, zero }));
  auto args = Value(Vector(alloc, { minus, n, one }));
  auto recur = Value(Vector(alloc, {factorial, args}));
  auto alt = Value(Vector(alloc, { mul, n, recur }));
  auto fact_body = Value(Vector(alloc, { iff, cond, one, alt }));
  auto fact_def = Value(Vector(alloc, { def, fact_sig, fact_body }));

  cout << fact_def << endl;

}

