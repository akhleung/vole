#ifndef VOLE_SLICE
#define VOLE_SLICE

#include <cstddef>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <initializer_list>

namespace Vole {

  using std::size_t;

  template <typename T>
  struct Slice {
    T*     mem;
    T*     beg;
    size_t len;
    size_t cap;

    template <typename Allocator>
    Slice(Allocator& a, size_t l, size_t c)
    : mem(a.template alloc<T>(c)),
      beg(mem),
      len(l),
      cap(c)
    { }

    Slice(T* m, T* b, size_t l, size_t c)
    : mem(m),
      beg(b),
      len(l),
      cap(c)
    { }
    // We'll also use the default copy constructors and assignment operators.

    T& operator[](size_t i) {
      if (!(i < len)) {
        // TODO: use an error class with more metadata
        throw "slice index out of bounds";
      }
      return beg[i];
    }

    Slice<T> slice(size_t lower, size_t upper) {
      if (upper > len || lower > upper) {
        // TODO: use an error class with more metadata
        throw "invalid range for slice";
      }
      return { mem, beg + lower, upper - lower, cap - lower };
    }

    T& first() {
      return (*this)[0];
    }

    T& head() {
      return first();
    }

    T& last() {
      return (*this)[len-1];
    }

    Slice<T> take(size_t n) {
      return slice(0, n);
    }

    Slice<T> drop(size_t n) {
      return slice(n, len);
    }

    Slice<T> take_half() {
      return take(len / 2);
    }

    Slice<T> drop_half() {
      return drop(len / 2);
    }

    template <typename Predicate>
    Slice<T> take_while(Predicate pred) {
      size_t i = 0;
      while (pred((*this)[i])) ++i;
      return take(i);
    }

    template <typename Predicate>
    Slice<T> drop_while(Predicate pred) {
      size_t i = 0;
      while (pred((*this)[i])) ++i;
      return drop(i);
    }

    Slice<T> tail() {
      return drop(1);
    }

    operator std::string() {
      std::stringstream ss;
      ss << '(';
      for (size_t i = 0; i < len; ++i) {
        ss << (i ? " " : "") << beg[i];
      }
      ss << ')';
      return ss.str();
    }

    std::string debug() {
      std::stringstream out;
      out << "len: " << len << ", cap: " << cap;
      return out.str();
    }
  };

  template<>
  Slice<const char>::operator std::string() {
    return std::string(beg, len);
  }

  template<>
  Slice<char>::operator std::string() {
    return std::string(beg, len);
  }

  template <typename T>
  void copy(Slice<T> src, Slice<T> dst) {
    size_t len = std::min(src.len, dst.len);
    if (src.beg < dst.beg && dst.beg < src.beg + len) {
      std::copy_backward(src.beg, src.beg + len, dst.beg + len);
    } else {
      std::copy(src.beg, src.beg + len, dst.beg);
    }
  }

  template <typename T, typename Allocator>
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

  template <typename T, typename Allocator>
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

  template <typename T, typename Allocator>
  Slice<T> append(Allocator alloc, Slice<T> s, std::initializer_list<T> l) {
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

#endif