#ifndef VOLE_VALUE
#define VOLE_VALUE

#include "slice.hpp"

namespace Vole {

  struct Value;
  using String = Slice<char>;
  using Vector = Slice<Value>;

  struct Value {
    enum Type {
      BOOLEAN,
      NUMBER,
      // SYMBOL,
      STRING,
      // REGEXP,
      VECTOR,
      // MAPPING
    } type;

    // for garbage collection
    enum Color {
      BLACK,
      GRAY,
      WHITE
    } color;

    union Content {
      bool    boolean;
      double  number;
      // wrapper around a String, every symbol with a name is unique
      // Symbol  symbol;
      String  string;
      // Regexp regexp;
      Vector  vector;
      // Mapping mapping;

      Content()                       { }
      Content(bool b)    : boolean(b) { }
      Content(double d)  : number(d)  { }
      // Content(Symbol s)  { new (&symbol) Symbol(s); }
      Content(String s)  : string(s)  { }
      Content(Vector v)  : vector(v)  { }
      // Content(Mapping m) { new (&mapping) Mapping(m); }
    } content;

    Value() { }

    template <typename T>
    Value(T thing, Color c = BLACK);

    template <typename IOS>
    IOS& serialize(IOS& ios);

    operator std::string();
  };

  template <>
  Value::Value(bool b, Color c)
  : type(BOOLEAN), color(c), content(b)
  { }

  template <>
  Value::Value(double d, Color c)
  : type(NUMBER), color(c), content(d)
  { }

  template <>
  Value::Value(String s, Color c)
  : type(STRING), color(c), content(s)
  { }

  template <>
  Value::Value(Vector v, Color c)
  : type(VECTOR), color(c), content(v)
  { }

  template <typename IOS>
  IOS& Value::serialize(IOS& ios) {
    switch (type) {
      case BOOLEAN: {
        ios << (content.boolean ? "#t" : "#f");
      } break;
      case NUMBER: {
        ios << content.number;
      } break;
      case STRING: {
        ios << content.string;
      } break;
      case VECTOR: {
        ios << content.vector;
      } break;
    }
    return ios;
  }

  template <typename IOS>
  IOS& operator<<(IOS& ios, Value val) {
    return val.serialize(ios);
  }

  Value::operator std::string() {
    std::stringstream ss;
    serialize(ss);
    return ss.str();
  }

}

#endif