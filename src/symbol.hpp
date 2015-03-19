#ifndef VOLE_SYMBOL
#define VOLE_SYMBOL

#include "slice.hpp"
#include <string>
#include <unordered_map>

namespace Vole {

  using String = Slice<char>;

  struct Symbol {
    String name;

    Symbol();
    Symbol(String s);
  };

  class Allocator;

  class Symbol_Table {
    std::unordered_map<std::string, Symbol> symbols;
  public:
    Symbol_Table();
    Symbol intern(Allocator& alloc, std::string name);
  };

}

#endif