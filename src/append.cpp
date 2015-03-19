#include "append.hpp"
#include "allocator.hpp"
#include "value.hpp"
#include <algorithm>

namespace Vole {

  using String = Slice<char>;
  using Vector = Slice<Value>;

  template <>
  String append(Allocator& A, String s, char c) {
    if (s.len < s.cap) {
      s.beg[s.len] = c;
      return { s.mem, s.beg, s.len+1, s.cap };
    } else {
      size_t cap = (s.cap ? s.cap * 2 : 1);
      char* mem = A.alloc_string(cap);
      String dest(mem, mem, s.len + 1, cap);
      copy(s, dest);
      dest.beg[s.len] = c;
      return dest;
    }
  }

  template <>
  Vector append(Allocator& A, Vector s, Value v) {
    if (s.len < s.cap) {
      s.beg[s.len] = v;
      return { s.mem, s.beg, s.len+1, s.cap };
    } else {
      size_t cap = (s.cap ? s.cap * 2 : 1);
      Value* mem = A.alloc_vector(cap);
      Vector dest(mem, mem, s.len + 1, cap);
      copy(s, dest);
      dest.beg[s.len] = v;
      return dest;
    }
  }

  template <>
  String append(Allocator& A, String s1, String s2) {
    if (s1.len + s2.len > s1.cap) {
      size_t cap = s1.len + s2.len;
      char* mem = A.alloc_string(cap);
      String dest(mem, mem, cap, cap);
      copy(s1, dest.take(s1.len));
      copy(s2, dest.drop(s1.len));
      return dest;
    } else {
      copy(s2, { s1.mem, s1.beg + s1.len, s2.len, s1.cap });
      return { s1.mem, s1.beg, s1.len + s2.len, s1.cap };
    }
  }

  template <>
  Vector append(Allocator& A, Vector s1, Vector s2) {
    if (s1.len + s2.len > s1.cap) {
      size_t cap = s1.len + s2.len;
      Value* mem = A.alloc_vector(cap);
      Vector dest(mem, mem, cap, cap);
      copy(s1, dest.take(s1.len));
      copy(s2, dest.drop(s1.len));
      return dest;
    } else {
      copy(s2, { s1.mem, s1.beg + s1.len, s2.len, s1.cap });
      return { s1.mem, s1.beg, s1.len + s2.len, s1.cap };
    }
  }

}