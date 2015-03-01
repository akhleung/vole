#include <iostream>
#include <sstream>
#include "slice.hpp"

using namespace std;


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
    cout << s.debug() << endl;
    if (s.len < s.cap) {
      s.beg[s.len] = t;
      return { s.mem, s.beg, s.len+1, s.cap };
    } else {
      Slice<T> newslice { alloc, s.len+1, s.cap*2 };
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



}


// using namespace Vole;

// class New {
// public:
//   template<typename T>
//   T* alloc(size_t size) {
//     cout << "Allocating " << size << " things!" << endl;
//     return new T[size];
//   }
// };

// int main() {
//   try {
//     auto my_new = New();
//     auto myslice = Slice<int>(my_new, 10, 10);
//     cout << "myslice: " << string(myslice) << endl;
//     auto myslice2 = append(my_new, myslice, 1);
//     cout << "myslice: " << string(myslice2) << endl;
//     auto myslice3 = append(my_new, myslice2, 2);
//     cout << "myslice: " << string(myslice3) << endl;

//     auto myslice4 = Slice<int>(my_new, 0, 0);
//     auto myslice5 = append(my_new, myslice4, 7);
//     cout << "myslice2: " << string(myslice5) << endl;
//     auto myslice6 = append(my_new, myslice5, 8);
//     auto myslice7 = append(my_new, myslice6, 9);
//     cout << "myslice2: " << string(myslice7) << endl;

//     auto myslice8 = append(my_new, myslice3, myslice7);
//     cout << "myslice: " << string(myslice8) << endl;
//   } catch(char const* err) {
//     cout << err << endl;
//   }

//   return 0;
// }