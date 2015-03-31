#include "env.hpp"

namespace Vole {
  Env::Env(Env* par)
  : parent(par) { }

  Value Env::lookup(Symbol name) {
    for (auto currentenv = this; currentenv; currentenv = currentenv->parent) {
      if (currentenv->bindings.count(name)) {
        return currentenv->bindings[name];
      }
    }
    return Value();
  }

  void Env::bind(Symbol name, Value value) {
    bindings[name] = value;
  }

  void Env::assign(Symbol name, Value value) {
    for (auto currentenv = this; currentenv; currentenv = currentenv->parent) {
      if (currentenv->bindings.count(name)) {
        currentenv->bindings[name] = value;
        return;
      }
    }
    throw "unbound variable!";
  }

}