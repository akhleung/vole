#include "env.hpp"

namespace Vole {

  Env::Env(Env* par)
  : parent(par) { }

  Value Env::lookup(Symbol name) {
    for (auto current = this; current; current = current->parent) {
      if (current->bindings.count(name)) {
        return current->bindings[name];
      }
    }
    throw "unbound variable";
  }

  void Env::bind(Symbol name, Value value) {
    bindings[name] = value;
  }

  void Env::assign(Symbol name, Value value) {
    for (auto current = this; current; current = current->parent) {
      if (current->bindings.count(name)) {
        current->bindings[name] = value;
        return;
      }
    }
    throw "assignment to unbound variable";
  }

}