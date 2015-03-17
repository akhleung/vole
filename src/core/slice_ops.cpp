#include "allocator.hpp"
#include "slice_ops.hpp"
#include <algorithm>

namespace Vole {

  template <typename T>
  void copy(Slice<T> src, Slice<T> dst) {
    size_t len = std::min(src.len, dst.len);
    if (src.beg < dst.beg && dst.beg < src.beg + len) {
      std::copy_backward(src.beg, src.beg + len, dst.beg + len);
    } else {
      std::copy(src.beg, src.beg + len, dst.beg);
    }
  }

  template <typename T>
  Slice<T> append(Allocator& alloc, Slice<T> s, T t) {
    if (s.len < s.cap) {
      s.beg[s.len] = t;
      return { s.mem, s.beg, s.len+1, s.cap };
    } else {
      Slice<T> dest { alloc, s.len+1, s.cap ? s.cap * 2 : 1 };
      copy(s, dest);
      dest.beg[s.len] = t;
      return dest;
    }
  }

  template <typename T>
  Slice<T> append(Allocator& alloc, Slice<T> s1, Slice<T> s2) {
    if (s1.len + s2.len > s1.cap) {
      Slice<T> dest { alloc, s1.len + s2.len, s1.len + s2.len };
      copy(s1, dest.take(s1.len));
      copy(s2, dest.drop(s1.len));
      return dest;
    } else {
      copy(s2, { s1.mem, s1.beg + s1.len, s2.len, s1.cap });
      return { s1.mem, s1.beg, s1.len + s2.len, s1.cap };
    }
  }

  template <typename T>
  Slice<T> append(Allocator& alloc, Slice<T> s, std::initializer_list<T> l) {
    if (s.len + l.size() > s.cap) {
      Slice<T> dest { alloc, s.len + l.size(), s.len + l.size() };
      copy(s, dest.take(s.len));
      std::copy(l.begin(), l.end(), dest.beg + s.len);
      return dest;
    } else {
      std::copy(l.begin(), l.end(), s.beg + s.len);
      return { s.mem, s.beg, s.len + l.size(), s.cap };
    }
  }

}