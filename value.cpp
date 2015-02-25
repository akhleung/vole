#include <iostream>

using namespace std;
struct Value;

template<typename T>
class Slice {
public:
  Slice(size_t len) : len_(len), cap_(len) {
    ptr_ = new T[cap_];
  }
  template<typename Allocator>
  Slice(size_t len, Allocator allocator) : len_(len), cap_(len) {
    ptr_ = allocator.template alloc<T>(len_);
  }
private:
  T*     ptr_;
  size_t len_;
  size_t cap_;
};

class New {
public:
  template<typename T>
  T* alloc(size_t size) {
    cout << "Allocating " << size << " things!" << endl;
    return new T[size];
  }
};

template<>
int* New::alloc(size_t size) {
  cout << "Allocating " << size << " ints!" << endl;
  return new int[size];
}


typedef Slice<int> int_slice;
typedef Slice<char> char_slice;
typedef Slice<Value> val_slice;

struct Value {
  enum {
    NUMBER,
    INT_SLICE,
    STRING,
    SLICE_HEADER
  } type;

  enum {
    BLACK,
    GRAY,
    WHITE
  } color;

  union Content {
    double number;
    int_slice ints;
    char_slice chars;
    val_slice vals;
    Content() { }
  } content;
};

int main() {
  cout << "size of Slice: " << sizeof(Slice<Value>) << endl;
  cout << "size of Value: " << sizeof(Value) << endl;
  auto ints = Slice<int>(20, New());
  cout << "size of ints: " << sizeof(ints) << endl;
  auto vals = Slice<Value>(14, New());
  cout << "size of vals: " << sizeof(vals) << endl;
  return 0;
}



