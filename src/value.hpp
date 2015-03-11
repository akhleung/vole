#ifndef VOLE_VALUE
#define VOLE_VALUE

#include <string>
#include <iostream>
#include "slice.hpp"

namespace Vole {

  struct Value;
  using String = Slice<char>;
  using Vector = Slice<Value>;

  struct Value {
    enum Type {
      BOOLEAN,
      NUMBER,
      SYMBOL,
      STRING,
      REGEXP,
      VECTOR,
      MAPPING
    } type;

    // for garbage collection
    enum Color {
      BLACK,
      GRAY,
      WHITE
    } color;

    union Content {
      bool boolean;
      double number;
      // Symbol symbol;
      String string;
      // Regexp regexp;
      Vector vector;
      // Mapping mapping;
      Content() { }

      

      Content(std::string s) {
        std::cout << "union string ctor" << std::endl; 
        new (&string) std::string(s);
      }

      Content(const Content& c) {
        std::cout << "union copy ctor" << std::endl;
      }

      ~Content() { }
    } content;

    Value(Type t, Color c = BLACK) : type(t), color(c) { }
    Value(std::string s) : type(STRING), color(BLACK), content {s} { }

    static Value make_boolean(bool b);
    static Value make_number(double n);
    static Value make_symbol(std::string s);
    static Value make_string(std::string s);

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