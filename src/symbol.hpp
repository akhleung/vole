#ifndef VOLE_SYMBOL
#define VOLE_SYMBOL

#include "slice.hpp"
// #include "value.hpp"
// #include "allocator.hpp"
#include <unordered_map>

namespace Vole {

  using String = Slice<char>;

  struct Symbol {
    String val;

    // Symbol()  { }
    Symbol(String s) : val(s) { }
  };

  // struct Symbol_Table {
  //   std::unordered_map<std::string, Symbol> symbols;

  //   Symbol_Table() { }

  //   // template <typename Allocator>
  //   Symbol intern_string(Allocator& alloc, std::string s);
  // };

  // template <typename Allocator>
  // Symbol Symbol_Table::intern_string(Allocator& alloc, std::string key) {
  //   auto sym = symbols.find(key);
  //   Symbol val;
  //   if ( sym == symbols.end() ) {
  //     auto it = symbols.insert(symbols.begin(), Symbol(String(alloc, key)));
  //     val = *it;
  //   } else {
  //     val = symbols[key];
  //   }
  //   return val;
  // }
}

#endif