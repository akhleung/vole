#ifndef VOLE_SLICE
#define VOLE_SLICE

#include <cstddef>
#include <string>
#include <sstream>

namespace Vole {

  using std::size_t;
  using std::string;

  template <typename T>
  struct Slice {
    T*     mem;
    T*     beg;
    size_t len;
    size_t cap;

    template <typename Allocator>
    Slice(Allocator& a, size_t l, size_t c);
    Slice(T* m, T* b, size_t l, size_t c);
    // We'll also use the default copy constructors and assignment operators.

    T& operator[](size_t i);
    Slice<T> slice(size_t start, size_t end); // s[start:end]

    T& first();              // s[0]
    T& last();               // s[len(s)-1]
    Slice<T> take(size_t n); // s[:n]
    Slice<T> drop(size_t n); // s[n:]

    template <typename P>
    Slice<T> take_while(P pred);
    template <typename P>
    Slice<T> drop_while(P pred);

    Slice<T> take_half();
    Slice<T> drop_half();

    operator string();

    string debug(); // prints length and cap

  };

  template <typename T, typename Allocator>
  Slice<T> append(Allocator& alloc, Slice<T> s, T t);
  template <typename T, typename Allocator>
  Slice<T> append(Allocator& alloc, Slice<T> s1, Slice<T> s2);

  using std::stringstream;

  template <typename T>
  template <typename Allocator>
  Slice<T>::Slice(Allocator& a, size_t l, size_t c)
  : mem(a.template alloc<T>(c)),
    beg(mem),
    len(l),
    cap(c)
  { }

  template <typename T>
  Slice<T>::Slice(T* m, T* b, size_t l, size_t c)
  : mem(m),
    beg(b),
    len(l),
    cap(c)
  { }

  template <typename T>
  T& Slice<T>::operator[](size_t i) {
    if (!(i < len)) {
      // TODO: use an error class with more metadata
      throw "slice index out of bounds";
    }
    return beg[i];
  }

  template <typename T>
  Slice<T> Slice<T>::slice(size_t lower, size_t upper) {
    if (upper > len || lower > upper) {
      // TODO: use an error class with more metadata
      throw "invalid range for slice";
    }
    return { mem, beg + lower, upper - lower, cap - lower };
  }

  template <typename T>
  T& Slice<T>::first() {
    return (*this)[0];
  }

  template <typename T>
  T& Slice<T>::last() {
    return (*this)[len-1];
  }

  template <typename T>
  Slice<T> Slice<T>::take(size_t n) {
    return slice(0, n);
  }

  template <typename T>
  Slice<T> Slice<T>::drop(size_t n) {
    return slice(n, len);
  }

  template <typename T>
  Slice<T>::operator string() {
    stringstream ss;
    ss << '(';
    for (size_t i = 0; i < len; ++i) {
      ss << (i ? " " : "") << beg[i];
    }
    ss << ')';
    return ss.str();
  }

  template <typename T>
  string Slice<T>::debug() {
    stringstream out;
    out << "len: " << len << ", cap: " << cap;
    return out.str();
  }

  template <typename T, typename Allocator>
  Slice<T> append(Allocator& alloc, Slice<T> s, T t) {
    if (s.len < s.cap) {
      s.beg[s.len] = t;
      return { s.mem, s.beg, s.len+1, s.cap };
    } else {
      Slice<T> newslice { alloc, s.len+1, (s.cap+1)*2 };
      for (int i = 0; i < s.len; i++) {
        newslice.beg[i] = s[i];
      }
      newslice.beg[s.len] = t;
      return newslice;
    }
  }


  template <typename T, typename Allocator>
  Slice<T> append(Allocator& alloc, Slice<T> s1, Slice<T> s2) {
    if (s1.len+s2.len < s1.cap) {
      for (int i = 0; i < s2.len; i++) {
        s1.beg[s1.len+i] = s2[i];
      }
      return { s1.mem, s1.beg, s1.len+s2.len, s1.cap };
    } else {
      Slice<T> newslice { alloc, s1.len+s2.len, (s1.cap+s2.len)*2 };
      for (int i = 0; i < s1.len; i++) {
        newslice.beg[i] = s1[i];
      }
      for (int i = 0; i < s2.len; i++) {
        newslice.beg[s1.len+i] = s2[i];
      }
      return newslice;
    }
  }

  template <typename T>
  template <typename P>
  Slice<T> Slice<T>::take_while(P pred) {
    for (size_t i = 0; i < len; i++) {
      if (!pred((*this)[i])) {
        return slice(0, i);
      }
    }
    return (*this);
  }

  template <typename T>
  template <typename P>
  Slice<T> Slice<T>::drop_while(P pred) {
    for (size_t i = 0; i < len; i++) {
      if (!pred((*this)[i])) {
        return slice(i, len);
      }
    }
    return (*this);
  }

  template <typename T>
  Slice<T> Slice<T>::take_half() {
    return slice(0, len/2);
  }

  template <typename T>
  Slice<T> Slice<T>::drop_half() {
    return slice(len/2, len);
  }

}

#endif