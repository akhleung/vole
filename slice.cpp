#include <iostream>
#include <sstream>
#include "slice.hpp"

namespace Vole {

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

  template <typename T, typename Allocator>
  Slice<T> append(Allocator& alloc, Slice<T> s, T t) {
    if (s.len < s.cap) {
      s[s.len] = t;
      Slice<T> newslice ( s.mem, s.beg, s.len+1, s.cap );
      return newslice;
    } else {
      auto newslice { alloc, s.len+1, s.cap*2 };
      for (int i = 0; i < s.len; i++) {
        newslice[i] = s[i];
      }
      newslice[s.len] = t;
      return newslice;
    }
  }


  template <typename T, typename Allocator>
  Slice<T> append(Allocator& alloc, Slice<T> s1, Slice<T> s2) {
    if (s1.len+s2.len < s1.cap) {
      for (int i = 0; i < s2.len; i++) {
        s1[s1.len+i] = s2[i];
      }
      return { s1.mem, s1.beg, s1.len+s2.len, s1.cap };
    } else {
      auto newslice { alloc, s1.len+s2.len, (s1.cap+s2.len)*2 };
      for (int i = 0; i < s1.len; i++) {
        newslice[i] = s1[i];
      }
      for (int i = 0; i < s2.len; i++) {
        newslice[s1.len+i] = s2[i];
      }
      return newslice;
    }
  }

}

using namespace std;
using namespace Vole;

class New {
public:
  template<typename T>
  T* alloc(size_t size) {
    cout << "Allocating " << size << " things!" << endl;
    return new T[size];
  }
};

int main() {
  auto my_new = New();
  auto myslice = Slice<int>(my_new, 10, 10);
  cout << "myslice: " << string(myslice) << endl;
  auto myslice2 = append(my_new, myslice, 1);
  // cout << "myslice: " << string(myslice2) << endl;
  // auto myslice3 = append(my_new, myslice, 2);
  // cout << "myslice: " << string(myslice3) << endl;
  // auto myslice4 = Slice<int>(my_new, 10, 10);
  // auto myslice5 = append(my_new, myslice2, 7);
  // auto myslice6 = append(my_new, myslice2, 8);
  // auto myslice7 = append(my_new, myslice2, 9);
  // cout << "myslice2: " << string(myslice7) << endl;

  // auto myslice8 = append(my_new, myslice, myslice2);
  // cout << "myslice: " << string(myslice8) << endl;


  return 0;
}