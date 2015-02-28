#ifndef VOLE_SLICE
#define VOLE_SLICE

#include <cstddef>
#include <string>

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
    // We'll also use the default copy constructors and assignment operators.

    T& operator[](size_t i);
    Slice<T> slice(size_t start, size_t end); // s[start:end]

    T& first();              // s[0]
    T& last();               // s[len(s)-1]
    Slice<T> take(size_t n); // s[:n]
    Slice<T> drop(size_t n); // s[n:]

    operator string();
  };

  template <typename T, typename Allocator>
  Slice<T> append(Allocator& alloc, Slice<T> s, T t);
  template <typename T, typename Allocator>
  Slice<T> concat(Allocator& alloc, Slice<T> s1, Slice<T> s2);

}

#endif