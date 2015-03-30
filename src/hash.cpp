#include "hash.hpp"
#include <functional>

using namespace Vole;
using namespace std;

size_t hash<Symbol>::operator()(Symbol sym) const {
  // TODO: do the right thing
  return hash<char*>()(sym.name.beg);
}
