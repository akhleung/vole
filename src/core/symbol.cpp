#include "symbol.hpp"
#include "allocator.hpp"

namespace Vole {

  using namespace std;

  Symbol::Symbol() { }
  Symbol::Symbol(String s) : name(s) { }

  Symbol_Table::Symbol_Table() { }
  Symbol Symbol_Table::intern(Allocator& alloc, std::string name) {
    if (symbols.count(name)) {
      return symbols[name];
    } else {
      auto len = name.length();
      auto mem = alloc.alloc_string(len);
      auto val = Symbol(String(mem, mem, len, len));
      // TODO: copy the chars too
      symbols[name] = val;
      return val;
    }
  }


}