#include "symbol.hpp"
#include "allocator.hpp"
#include <algorithm>

namespace Vole {

  using namespace std;

  Symbol::Symbol() { }
  Symbol::Symbol(String s) : name(s) { }

  Symbol_Table::Symbol_Table() { }
  Symbol Symbol_Table::intern(Allocator& A, const std::string& name) {
    if (symbols.count(name)) {
      return symbols[name];
    } else {
      auto sym = Symbol(String(A, name));
      symbols[name] = sym;
      return sym;
    }
  }

}