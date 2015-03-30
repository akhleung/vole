#include "env.hpp"

namespace Vole {
  Env::Env(Env* par)
  : parent(par) { }

  Value Env::lookup(Symbol name) {
    if (bindings.count(name)) {
      return bindings[name];
    } else {
      if (parent) {
        auto cur = parent;
        for (auto c = cur; c != nullptr; c = c->parent) {
          if (c->bindings.count(name)) {
            return c->bindings[name];
          }
        }
      }
    }
    return Value();
  }

  void Env::bind(Symbol name, Value value) {
    bindings[name] = value;
  }

  void Env::assign(Symbol name, Value value) {
    if (bindings.count(name)) {
      bindings[name] = value;
    } else {
      auto cur = parent;
      for (auto c = cur; c != nullptr; c = c->parent) {
        if (c->bindings.count(name)) {
          c->bindings[name] = value;
          return;
        }
      }
      bind(name, value);
    }
  }

}