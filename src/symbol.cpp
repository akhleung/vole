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
      auto len = name.length();
      auto mem = A.alloc_string(len);
      copy(name.begin(), name.end(), mem);
      auto sym = Symbol(String(mem, mem, len, len));
      symbols[name] = sym;
      return sym;
    }
  }

}