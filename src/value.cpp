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
  using std::string;

  Value Value::make_boolean(bool b) {
    Value v { BOOLEAN };
    v.content.boolean = b;
    return v;
  }

  Value Value::make_number(double n) {
    Value v { NUMBER };
    v.content.number = n;
    return v;
  }

  Value Value::make_symbol(string s) {
    Value v { SYMBOL };
    v.content.symbol = s;
    return v;
  }

  Value Value::make_string(string s) {
    Value v { STRING };
    std::cout << "about to assign to union" << std::endl;
    v.content.string = s;
    return v;
  }

}

using namespace Vole;
using namespace std;

int main() {
  auto alloc = Allocator();
  cout << "size of value: " << sizeof(Value) << endl;
  Value val = Value::make_boolean(true);
  cout << "size of bval: " << sizeof(val) << endl;
  cout << "value of bval: " << val.content.boolean << endl;
  Value num = Value::make_number(3.14);
  cout << "size of num: " << sizeof(num) << endl;
  cout << "value of num: " << num.content.number << endl;
  // Value str = Value::make_string("hello there");
  // cout << "size of str: " << sizeof(str) << endl;
  // cout << "value of str: " << str.content.string << endl;

  auto str2 = Value(string("another string"));
  cout << "size of str2: " << sizeof(str2) << endl;
  cout << "value of str2: " << str2.content.string << endl;
}