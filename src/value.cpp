#include "value.hpp"
#include "allocator.hpp"
#include <iostream>

namespace Vole {

  // template <typename Allocator>
  // Value Value::make_boolean(Allocator& alloc, bool b) {
  //   Value v { BOOLEAN, BLACK };
  //   v.content.boolean = false;
  //   return v;
  // }

  Value make_boolean(bool b) {
    Value v { Value::BOOLEAN, Value::BLACK };
    v.content.boolean = b;
    return v;
  }



}

using namespace Vole;
using namespace std;

int main() {
  auto alloc = Allocator();
  cout << "size of value: " << sizeof(Value) << endl;
  Value val = make_boolean(true);
  cout << "size of bval: " << sizeof(val) << endl;
  cout << "value of bval: " << val.content.boolean << endl;

}