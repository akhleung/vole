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
    return new T[size];
  }
};

typedef Slice<int> int_slice;
typedef Slice<char> char_slice;
typedef Slice<Value> val_slice;

struct Value {
  enum {
    NUMBER,
    INT_SLICE,
    STRING
  } type;

  enum {
    BLACK,
    GRAY,
    WHITE
  } color;

  union {
    double number;
    int_slice ints;
    char_slice chars;
    val_slice vals;
  } content;
};

int main() {
  cout << "size of Slice: " << sizeof(Slice<Value>) << endl;
  cout << "size of Value: " << sizeof(Value) << endl;
  auto ints = Slice<int>(20, New());
  cout << "size of ints: " << sizeof(ints) << endl;
  return 0;
}



