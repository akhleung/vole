#include "slice.hpp"
#include "allocator.hpp"
#include "value.hpp"
#include <string>

namespace Vole {

  using namespace std;

  template <>
  Slice<char>::Slice(Allocator& A, const string& str)
  : mem(A.alloc_chars(str.size())), beg(mem), len(str.size()), cap(len) {
    std::copy(str.begin(), str.end(), mem);
  }

  template <>
  Slice<Value>::Slice(Allocator& A, const initializer_list<Value>& lst)
  : mem(A.alloc_values(lst.size())), beg(mem), len(lst.size()), cap(len) {
    std::copy(lst.begin(), lst.end(), mem);
  }

  template <>
  Slice<Value>::Slice(Allocator& A, const vector<Value>& vec)
  : mem(A.alloc_values(vec.size())), beg(mem), len(vec.size()), cap(len) {
    std::copy(vec.begin(), vec.end(), mem);
  }

}