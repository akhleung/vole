#include <cctype>
#include <iostream>
#include <string>
#include "slice.hpp"
#include "allocator.hpp"


using namespace std;
using namespace Vole;

int munchToken(char* c, Slice<string> res, Allocator alloc) {
  int i = 0;
  while (!isspace(c[i])) {
    i++;
  }
  res = append(alloc, res, string(c, i));
  return i;
}

string munch(char* src, Slice<string> result, Allocator alloc) {
  char c;
  int i = 0;
  while(src[i]) {
    c = src[i];
    if(strcmp(c, "(")) {
      auto newslice = Slice<string>(alloc, 0, 0);
      string sub = munch(c, newslice, alloc);
      result = append(alloc, result, sub);
    } else if (strcmp(c, ")")) {
      return string(result);
    } else if(!isspace(c)) {
      i += munchToken(c, result, alloc);
    } else if(isspace(c)) {
      i++;
    }
  }
  return string(result);
}

int main() {
  auto alloc = Allocator();
  auto res = Slice<string>(alloc, 0, 0);
  string result = munch("(hello (one two (three) ) )", res, alloc);
  cout << result << endl;
}