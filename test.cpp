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
    auto alloc = New();
    auto myslice = Slice<int>(alloc, 10, 10);
    cout << "myslice: " << string(myslice) << endl;
    auto myslice2 = append(alloc, myslice, 1);
    cout << "myslice: " << string(myslice2) << endl;
    auto myslice3 = append(alloc, myslice2, 2);
    cout << "myslice: " << string(myslice3) << endl;

    auto myslice4 = Slice<int>(alloc, 0, 0);
    auto myslice5 = append(alloc, myslice4, 7);
    cout << "myslice2: " << string(myslice5) << endl;
    auto myslice6 = append(alloc, myslice5, 8);
    auto myslice7 = append(alloc, myslice6, 9);
    cout << "myslice2: " << string(myslice7) << endl;

    auto myslice8 = append(alloc, myslice3, myslice7);
    cout << "myslice: " << string(myslice8) << endl;
    auto myslice9 = myslice8.take_half();
    cout << "myslice take half: " << string(myslice9) << endl;
    auto myslice10 = myslice9.drop_half();
    cout << "myslice drop half: " << string(myslice10) << endl;



    auto myslice11 = Slice<int>(alloc, 0, 0);
    auto myslice12 = append(alloc, myslice11, 1);
    auto myslice13 = append(alloc, myslice12, 2);
    auto myslice14 = append(alloc, myslice13, 3);
    auto myslice15 = append(alloc, myslice14, 4);
    auto myslice16 = append(alloc, myslice15, 5);
    auto myslice17 = append(alloc, myslice16, 6);
    auto myslice18 = append(alloc, myslice17, 7);
    auto myslice19 = append(alloc, myslice18, 8);
    auto myslice20 = append(alloc, myslice19, 9);
    auto myslice21 = append(alloc, myslice20, 10);

    auto myslice22 = myslice21.take_while(lessthan5);
    cout << "myslice take while less than 5: " << string(myslice22) << endl;
    auto myslice23 = myslice21.drop_while(lessthan5);
    cout << "myslice drop while less than 5: " << string(myslice23) << endl;
    cout << "myslice take half: " << string(myslice23.take_half()) << endl;
    cout << "myslice drop half: " << string(myslice23.drop_half()) << endl;

    auto myString = Slice<char>(alloc, 0, 3);
    myString = append(alloc, myString, 'a');
    myString = append(alloc, myString, 'b');
    myString = append(alloc, myString, 'c');
    cout << "mystring: " << string(myString) << endl;

    auto myMsg = Slice<string>(alloc, 0, 10);
    myMsg = Vole::fill(alloc, myMsg, initializer_list<string>{"hello", "my", "name", "is", "Aaron"});
    cout << "myMsg: " << string(myMsg) << endl;


  } catch(char const* err) {
    cout << err << endl;
  }


  return 0;
}