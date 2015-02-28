#include <sstream>
#include "slice.hpp"

namespace Vole {

  using std::stringstream;

  template <typename T>
  Slice<T>::Slice(size_t l, size_t c)
  : mem(new T[c]),
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
  template <typename Allocator>
  Slice<T>::Slice(size_t l, size_t c, Allocator& a)
  : mem(a.template alloc<T>(c)),
    beg(mem),
    len(l),
    cap(c)
  { }

  template <typename T>
  template <typename Allocator>
  Slice<T>::Slice(size_t l, size_t c, Allocator* a)
  : mem(a->template alloc<T>(c)),
    beg(mem),
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
  Slice<T> Slice<T>::slice(size_t start, size_t end) {
    if (end > len || start > end) {
      // TODO: use an error class with more metadata
      throw "invalid range for slice";
    }
    return { mem, beg + start, end - beg, cap };
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
}