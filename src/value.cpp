#include "value.hpp"

namespace Vole {

  Value::Content::Content()                      { }
  Value::Content::Content(bool b)   : boolean(b) { }
  Value::Content::Content(double d) : number(d)  { }
  Value::Content::Content(Symbol s) : symbol(s)  { }
  Value::Content::Content(String s) : string(s)  { }
  Value::Content::Content(Vector v) : vector(v)  { }
  Value::Content::Content(char c)   : color(c)   { }

  Value::Value()         : type(UNDEFINED)           { }
  Value::Value(bool b)   : type(BOOLEAN), content(b) { }
  Value::Value(double d) : type(NUMBER),  content(d) { }
  Value::Value(Symbol s) : type(SYMBOL),  content(s) { }
  Value::Value(String s) : type(STRING),  content(s) { }
  Value::Value(Vector v) : type(VECTOR),  content(v) { }
  Value::Value(char c)   : type(COLOR),   content(c) { }

}