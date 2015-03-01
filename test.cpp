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

bool lessthan5(int x) {
  if (x < 5) {
    return true;
  } else {
    return false;
  }
}

int main() {
  try {
    auto my_new = New();
    auto myslice = Slice<int>(my_new, 10, 10);
    cout << "myslice: " << string(myslice) << endl;
    auto myslice2 = append(my_new, myslice, 1);
    cout << "myslice: " << string(myslice2) << endl;
    auto myslice3 = append(my_new, myslice2, 2);
    cout << "myslice: " << string(myslice3) << endl;

    auto myslice4 = Slice<int>(my_new, 0, 0);
    auto myslice5 = append(my_new, myslice4, 7);
    cout << "myslice2: " << string(myslice5) << endl;
    auto myslice6 = append(my_new, myslice5, 8);
    auto myslice7 = append(my_new, myslice6, 9);
    cout << "myslice2: " << string(myslice7) << endl;

    auto myslice8 = append(my_new, myslice3, myslice7);
    cout << "myslice: " << string(myslice8) << endl;
    auto myslice9 = myslice8.take_half();
    cout << "myslice take half: " << string(myslice9) << endl;
    auto myslice10 = myslice9.drop_half();
    cout << "myslice drop half: " << string(myslice10) << endl;



    auto myslice11 = Slice<int>(my_new, 0, 0);
    auto myslice12 = append(my_new, myslice11, 1);
    auto myslice13 = append(my_new, myslice12, 2);
    auto myslice14 = append(my_new, myslice13, 3);
    auto myslice15 = append(my_new, myslice14, 4);
    auto myslice16 = append(my_new, myslice15, 5);
    auto myslice17 = append(my_new, myslice16, 6);
    auto myslice18 = append(my_new, myslice17, 7);
    auto myslice19 = append(my_new, myslice18, 8);
    auto myslice20 = append(my_new, myslice19, 9);
    auto myslice21 = append(my_new, myslice20, 10);

    auto myslice22 = myslice21.take_while(lessthan5);
    cout << "myslice take while less than 5: " << string(myslice22) << endl;
    auto myslice23 = myslice21.drop_while(lessthan5);
    cout << "myslice drop while less than 5: " << string(myslice23) << endl;


  } catch(char const* err) {
    cout << err << endl;
  }


  return 0;
}