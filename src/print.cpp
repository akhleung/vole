#include "print.hpp"
#include <sstream>

namespace Vole {

  using namespace std;

  string print(String str) {
    return string(str.beg, str.beg + str.len);
  }

  string print(Vector vec) {
    stringstream ss;
    ss << '(';
    if (vec.len) {
      ss << print(vec.head());
      for (auto val : vec.tail()) ss << ' ' << print(val);
    }
    ss << ')';
    return ss.str();
  }

  string print(Symbol sym) {
    return print(sym.name);
  }

  string print(Value val) {
    stringstream ss;
    switch (val.type) {
      case Value::BOOLEAN:
        ss << (val.content.boolean ? "#t" : "#f");
        break;
      case Value::NUMBER:
        ss << val.content.number;
        break;
      case Value::SYMBOL:
        ss << print(val.content.symbol);
        break;
      case Value::STRING:
        ss << print(val.content.string);
        break;
      case Value::VECTOR:
        ss << print(val.content.vector);
        break;
      case Value::FUNCTION:
        ss << "[function]";
        break;
      default:
        break;
    }
    return ss.str();
  }

}