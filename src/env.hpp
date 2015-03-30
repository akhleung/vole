#ifndef VOLE_ENV
#define VOLE_ENV

#include "value.hpp"
#include "hash.hpp"
#include "eq.hpp"
#include <unordered_map>

namespace Vole {

  class Env {
  public:
    Env(Env* par = nullptr);
    Value lookup(Symbol name);
    void bind(Symbol name, Value value);
    void assign(Symbol name, Value value);
  private:
    std::unordered_map<Symbol, Value> bindings;
    Env* parent;
  };

}

#endif