#include <iostream>
#include "slice.hpp"

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
  try {
    auto my_new = New();
    auto myslice = Slice<int>(my_new, 10, 10);
    cout << "myslice: " << string(myslice) << endl;
    auto myslice2 = append(my_new, myslice, 1);
    cout << "myslice: " << string(myslice2) << endl;
    auto myslice3 = append(my_new, myslice2, 2);
    cout << "myslice: " << string(myslice3) << endl;

    auto myslice4 = Slice<int>(my_new, 10, 10);
    auto myslice5 = append(my_new, myslice4, 7);
    cout << "myslice2: " << string(myslice5) << endl;
    auto myslice6 = append(my_new, myslice5, 8);
    auto myslice7 = append(my_new, myslice6, 9);
    cout << "myslice2: " << string(myslice7) << endl;

    auto myslice8 = append(my_new, myslice3, myslice7);
    cout << "myslice: " << string(myslice8) << endl;
  } catch(char const* err) {
    cout << err << endl;
  }


  return 0;
}