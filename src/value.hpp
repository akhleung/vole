#ifndef VOLE_VALUE
#define VOLE_VALUE

#include <string>
#include "slice.hpp"

namespace Vole {

  struct Value;
  using Vector = Slice<Value>;

  struct Value {
    enum Type {
      BOOLEAN,
      NUMBER,
      SYMBOL,
      STRING,
      VECTOR
    } type;

    enum Color {
      BLACK,
      GRAY,
      WHITE
    } color;

    union Content {
      bool boolean;
      double number;
      std::string symbol; // TODO: use our own symbol object
      std::string string;
      Vector vector;
      Content() { }
      Content(const Content& c) { }
      ~Content() { }
    } content;

    Value(Type t, Color c) : type(t), color(c) { }

    // template <typename Allocator>
    // static Value make_boolean(Allocator& alloc, bool b) {
    //   Value v(BOOLEAN, BLACK);
    //   v.content.boolean = b;
    //   return v;
    // }
    // template <typename Allocator>
    // static Value make_number(Allocator& alloc, double n);
    // template <typename Allocator>
    // static Value make_symbol(Allocator& alloc, std::string s);
    // template <typename Allocator>
    // static Value make_string(Allocator& alloc, std::string s);
    // template <typename Allocator>
    // static Value make_vector(Allocator& alloc, size_t len = 0);
    // template <typename Allocator>
    // static Value make_vector(Allocator& alloc, size_t len, size_t cap);
  };

}

#endif