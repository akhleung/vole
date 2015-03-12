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
      // wrapper around a String, every symbol with a name is unique
      // Symbol symbol;
      String string;
      // Regexp regexp;
      Vector vector;
      // Mapping mapping;
      Content() { }

      template <typename Allocator> 
      Content(Allocator& alloc, std::string str) {
        std::cout << "string constructor" << std::endl;
        new (&string) String(alloc, str.size(), str.size());
        std::copy(str.begin(), str.end(), string.beg);
      }

      template <typename Allocator> 
      Content(Allocator& alloc, size_t len, size_t cap) {
        std::cout << "vector constructor" << std::endl;
        new (&vector) Vector(alloc, len, cap);
      }

      template <typename Allocator> 
      Content(Allocator& alloc, std::initializer_list<Value> l) {
        std::cout << "initializer list constructor" << std::endl;
        new (&vector) Vector(alloc, l);
      }

      // Content(std::string s) {
      //   std::cout << "union string ctor" << std::endl; 
      //   new (&string) std::string(s);
      // }

      Content(const Content& c) {
        std::cout << "union copy ctor" << std::endl;
      }

      ~Content() { }
    } content;

    template <typename T>
    Value(T thing, Color c = BLACK) { }

    Value(Type t, Color c = BLACK): type(t), color(c) { }
    template <typename Allocator>
    Value(Allocator& alloc, std::string s) : type(STRING), color(BLACK), content(alloc, s) { }
    template <typename Allocator>
    Value(Allocator& alloc, size_t len, size_t cap) : type(VECTOR), color(BLACK), content(alloc, len, cap) { }
    template <typename Allocator>
    Value(Allocator& alloc, std::initializer_list<Value> l) : type(VECTOR), color(BLACK), content(alloc, l) { }

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

  template <>
  Value::Value<bool>(bool b, Color c)
  : type(BOOLEAN), color(c)
  { }

  template <>
  Value::Value<double>(double d, Color c)
  : type(NUMBER), color(c)
  { }

  template <>
  Value::Value<String>(String s, Color c)
  : type(STRING), color(c)
  { }

  template <>
  Value::Value<Vector>(Vector v, Color c)
  : type(VECTOR), color(c)
  { }

}

#endif