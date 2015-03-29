#ifndef VOLE_ENV
#define VOLE_ENV

#include <unordered_map>

namespace Vole {

  class Env {
  public:
    Env(Env* par = nullptr);
    Value lookup(Symbol name);
    void insert(Symbol name, Value value);
  private:
    std::unordered_map<Symbol, Value> bindings;
    Env* parent;
  };

}

#endif