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

      Content(bool b)    : boolean(b) { }
      Content(double d)  : number(d)  { }
      // Content(Symbol s) { new (&symbol) Symbol(s); }
      Content(String s)  { new (&string) String(s); }
      Content(Vector v)  { new (&vector) Vector(v); }
      // Content(Mapping m) { new (&mapping) Mapping(m); }
    } content;

    template <typename T>
    Value(T thing, Color c = BLACK)
    : type(BOOLEAN), color(c), content(true)
    { }

    operator std::string() {
      std::stringstream ss;
      switch (type) {
        case BOOLEAN: {
          ss << (content.boolean ? "#t" : "#f");
        } break;
        case NUMBER: {
          ss << content.number;
        } break;
        case STRING: {
          ss << content.string;
        } break;
        case VECTOR: {
          ss << content.vector;
        } break;
      }
      return ss.str();
    }
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
  IOS& operator<<(IOS& ios, Value val) {
    switch (val.type) {
      case Value::BOOLEAN: {
        ios << (val.content.boolean ? "#t" : "#f");
      } break;
      case Value::NUMBER: {
        ios << val.content.number;
      } break;
      case Value::STRING: {
        ios << val.content.string;
      } break;
      case Value::VECTOR: {
        ios << val.content.vector;
      } break;
    }
    return ios;
  }

}

#endif