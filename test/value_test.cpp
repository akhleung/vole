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

}