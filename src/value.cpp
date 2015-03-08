#include <iostream>

using namespace std;
struct Value;

template<typename T>
class Slice {

public:

  Slice(size_t len)
  : mem_(new T[len]),
    beg_(mem_),
    len_(len),
    cap_(len)
  { }

  template<typename Allocator>
  Slice(size_t len, Allocator& allocator)
  : mem_(allocator.template alloc<T>(len)),
    beg_(mem_),
    len_(len),
    cap_(len)
  { }

  template<typename Allocator>
  Slice(size_t len, Allocator* allocator)
  : mem_(allocator->template alloc<T>(len)),
    beg_(mem_),
    len_(len),
    cap_(len)
  { }

private:

  T*     mem_;
  T*     beg_;
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
  enum Type {
    NUMBER,
    INT_SLICE,
    STRING,
  } type;

  enum Color {
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
  auto my_new = New();
  auto ints = Slice<int>(20, my_new);
  cout << "size of ints: " << sizeof(ints) << endl;
  auto vals = Slice<Value>(14, &my_new);
  cout << "size of vals: " << sizeof(vals) << endl;
  return 0;
}
