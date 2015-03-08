#include <iostream>
#include "../src/slice.hpp"

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

using Strs = Slice<const char*>;
using Ints = Slice<int>;

int main() {
  auto alloc = New();

  auto empty = Strs(alloc, 0, 0);
  cout << "empty slice: " << string(empty) << endl;

  auto not_so_empty = append(alloc, empty, "not");
  not_so_empty = append(alloc, not_so_empty, "so");
  not_so_empty = append(alloc, not_so_empty, "empty");
  cout << "not-so-empty slice: " << string(not_so_empty) << endl;
  cout << "empty slice: " << string(empty) << endl;

  auto still_not_so_empty = Strs(alloc, { "still" });
  still_not_so_empty = append(alloc, still_not_so_empty, not_so_empty);
  cout << "still not-so-empty: " << string(still_not_so_empty) << endl;
  cout << "not-so-empty slice: " << string(not_so_empty) << endl;

  auto more_room_than_needed = Strs(alloc, 0, 10);
  more_room_than_needed = append(alloc, more_room_than_needed, { "hello", "my", "name", "is", "Aaron" });
  cout << "more room than needed: " << string(more_room_than_needed) << endl;

  auto and_dont_wear_it_out = append(alloc, more_room_than_needed, { "and", "don't", "wear", "it", "out!" });
  cout << "and don't wear it out!: " << string(and_dont_wear_it_out) << endl;
  cout << "more room than needed: " << string(more_room_than_needed) << endl;

  auto upto10 = Ints(alloc, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
  cout << "up to 10: " << string(upto10) << endl;

  auto lessthan5 = upto10.take_while([](int x) { return x < 5; });
  auto morethan4 = upto10.drop_while([](int x) { return x < 5; });
  cout << "less than 5: " << string(lessthan5) << endl;
  cout << "more than 4: " << string(morethan4) << endl;
  cout << "up to 10: " << string(upto10) << endl;

  auto rotated = append(alloc, morethan4, lessthan5);
  cout << "rotated: " << string(rotated) << endl;
  cout << "less than 5: " << string(lessthan5) << endl;
  cout << "more than 4: " << string(morethan4) << endl;
  cout << "up to 10: " << string(upto10) << endl;

  auto upto10again = append(alloc, rotated.drop_half(), rotated.take_half());
  cout << "up to 10 again: " << string(upto10again) << endl;

  return 0;
}