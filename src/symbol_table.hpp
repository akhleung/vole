#ifndef VOLE_SYMBOL_TABLE
#define VOLE_SYMBOL_TABLE

#include "symbol.hpp"
#include <unordered_map>

namespace Vole {

  struct Symbol_Table {
    std::unordered_map<std::string, Symbol> symbols;

    Symbol_Table() { }

    template <typename Allocator>
    Symbol intern_string(Allocator& alloc, std::string s);
  };

  template <typename Allocator>
  Symbol Symbol_Table::intern_string(Allocator& alloc, std::string key) {
    if (symbols.count(key)) {
      return symbols[key];
    } else {
      auto val = Symbol(String(alloc, key));
      symbols[key] = val;
      return val;
    }
  }
}

#endif