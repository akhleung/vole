#ifndef VOLE_SLICE
#define VOLE_SLICE

#include <algorithm>
#include <cstddef>

namespace Vole {

  class Allocator;
  class Value;

  template <typename T>
  struct Slice {
    T*          mem;
    T*          beg;
    std::size_t len;
    std::size_t cap;

    Slice()
    : mem(nullptr), beg(mem), len(0), cap(0)
    { }

    Slice(T* m, std::size_t c)
    : mem(m), beg(m), len(c), cap(c)
    { }

    Slice(T* m, T* b, std::size_t l, std::size_t c)
    : mem(m), beg(b), len(l), cap(c)
    { }

    Slice(Allocator& A, const std::string& str);
    Slice(Allocator& A, const std::initializer_list<Value>& lst);
    Slice(Allocator& A, const std::vector<Value>& vec);

    T* begin() { return beg; }
    T* end()   { return beg + len; }

    T& operator[](std::size_t i) {
      if (!(i < len)) {
        // TODO: use an error class with more metadata
        throw "slice index out of bounds";
      }
      return beg[i];
    }

    Slice<T> slice(std::size_t lower, std::size_t upper) {
      if (upper > len || lower > upper) {
        // TODO: use an error class with more metadata
        throw "invalid range for slice";
      }
      return { mem, beg + lower, upper - lower, cap - lower };
    }

    T&       first()             { return (*this)[0]; }
    T&       last()              { return (*this)[len-1]; }
    T&       head()              { return first(); }
    Slice<T> tail()              { return slice(1, len); }
    Slice<T> rest()              { return tail(); }
    Slice<T> take(std::size_t n) { return slice(0, n); }
    Slice<T> drop(std::size_t n) { return slice(n, len); }
    Slice<T> take_half()         { return take(len / 2); }
    Slice<T> drop_half()         { return drop(len / 2); }

    template <typename Predicate>
    Slice<T> take_while(Predicate pred) {
      std::size_t i = 0;
      while (pred((*this)[i])) ++i;
      return take(i);
    }

    template <typename Predicate>
    Slice<T> drop_while(Predicate pred) {
      std::size_t i = 0;
      while (pred((*this)[i])) ++i;
      return drop(i);
    }

  };

  template <typename T>
  void copy(Slice<T> src, Slice<T> dst) {
    size_t len = std::min(src.len, dst.len);
    if (src.beg < dst.beg && dst.beg < src.beg + len) {
      std::copy_backward(src.beg, src.beg + len, dst.beg + len);
    } else {
      std::copy(src.beg, src.beg + len, dst.beg);
    }
  }

}

#endif