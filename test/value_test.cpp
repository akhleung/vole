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

}