#ifndef VOLE_SLICE
#define VOLE_SLICE

#include <cstddef>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <initializer_list>

namespace Vole {

  using std::size_t;

  struct Value;
  template <typename T> struct Slice;
  using String = Slice<char>;
  using Vector = Slice<Value>;

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

    template <typename Allocator>
    Slice(Allocator& a, std::initializer_list<T> l)
    : mem(a.template alloc<T>(l.size())),
      beg(mem),
      len(l.size()),
      cap(len)
    { std::copy(l.begin(), l.end(), beg); }

    template <typename Allocator>
    Slice(Allocator& a, const char* str)
    : Slice(a, std::strlen(str), std::strlen(str))
    { }

    template <typename Allocator>
    Slice(Allocator& a, std::string str)
    : Slice(a, str.c_str())
    { }

    Slice(T* m, T* b, size_t l, size_t c)
    : mem(m),
      beg(b),
      len(l),
      cap(c)
    { }
    // We'll also use the default copy constructors and assignment operators.

    T* begin() { return beg; }
    T* end()   { return beg + len; }

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

    T&       first()        { return (*this)[0]; }
    T&       last()         { return (*this)[len-1]; }
    T&       head()         { return first(); }
    Slice<T> tail()         { return slice(1, len); }
    Slice<T> take(size_t n) { return slice(0, n); }
    Slice<T> drop(size_t n) { return slice(n, len); }
    Slice<T> take_half()    { return take(len / 2); }
    Slice<T> drop_half()    { return drop(len / 2); }

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

    operator std::string() {
      std::stringstream ss;
      ss << (*this);
      return ss.str();
    }

    std::string debug() {
      std::stringstream out;
      out << "len: " << len << ", cap: " << cap;
      return out.str();
    }
  };

  template <>  
  template <typename Allocator>
  Slice<char>::Slice(Allocator& a, const char* str) {
    len = cap = std::strlen(str);
    beg = mem = a.template alloc<char>(cap);
    std::copy(str, str + len, mem);
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

  template <typename Allocator>
  Slice<char> slice_from_string(Allocator& alloc, const char* str, size_t n) {
    auto result = Slice<char>(alloc, n, n);
    std::copy(str, str + n, result.beg);
    return result;
  }

  template <typename Allocator>
  Slice<char> slice_from_string(Allocator& alloc, const char* str) {
    auto n = std::strlen(str);
    auto result = Slice<char>(alloc, n, n);
    std::copy(str, str + n, result.beg);
    return result;
  }

  template <typename Allocator>
  Slice<char> slice_from_string(Allocator& alloc, std::string str) {
    auto result = Slice<char>(alloc, str.size(), str.size());
    std::copy(str.begin(), str.end(), result.beg);
    return result;
  }

  template <typename IOS, typename T>
  IOS& operator<<(IOS& ios, Slice<T> s) {
    ios << '(';
    for (size_t i = 0; i < s.len; ++i) {
      ios << (i ? " " : "") << s[i];
    }
    ios << ')';
    return ios;
  }

  template <typename IOS>
  IOS& operator<<(IOS& ios, Slice<char> s) {
    for (char c : s) ios << c;
    return ios;
  }

  template<>
  Slice<char>::operator std::string() {
    return std::string(beg, len);
  }

}

#endif