#ifndef VOLE_VALUE
#define VOLE_VALUE

#include "slice.hpp"
#include "symbol.hpp"
#include "function.hpp"

namespace Vole {

  struct Value {
    enum Type {
      UNDEFINED,
      BOOLEAN,
      NUMBER,
      SYMBOL,
      STRING,
      // REGEXP,
      VECTOR,
      // MAPPING,
      FUNCTION,
      COLOR // for garbage collection; expected values are 'b', 'g', and 'w'
    } type;

    union Content {
      bool     boolean;
      double   number;
      Symbol   symbol;
      String   string;
      Vector   vector;
      Function function;
      char     color;

      Content();
      Content(bool b);
      Content(double d);
      Content(Symbol s);
      Content(String s);
      Content(Vector v);
      Content(Function f);
      Content(char c);
    } content;

    Value();
    Value(bool b);
    Value(double d);
    Value(Symbol s);
    Value(String s);
    Value(Vector v);
    Value(Function f);
    Value(char c);

    operator bool();
  };

}

#endif