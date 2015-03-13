#include "../src/slice.hpp"
#include "../src/value.hpp"
#include "../src/allocator.hpp"
#include <iostream>

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


}

