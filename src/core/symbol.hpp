#ifndef VOLE_SYMBOL
#define VOLE_SYMBOL

#include "allocator.hpp"
#include "slice.hpp"
#include <unordered_map>

namespace Vole {

  using String = Slice<char>;

  struct Symbol {
    String val;

    Symbol() { }
    Symbol(String s) : val(s) { }
  };

  // class Allocator;

  class Symbol_Table {
    std::unordered_map<std::string, Symbol> symbols;
  public:
    Symbol_Table() { }
    Symbol intern(Allocator& alloc, std::string name) {
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
  };

}

#endif