#ifndef VOLE_SLICE
#define VOLE_SLICE

#include <string>
#include <vector>

namespace Vole {

  template<typename T>
  class Slice {
  public:
    Slice(size_t cap = 0, std::vector<T> *cont = new std::vector<T>()) : start(0), end(cap), contents(cont) {
      contents.reserve(cap);
    }
    Slice* push(T t) {
      contents.push_back(t);
      end++;
      return new Slice(end, contents);
    }
    Slice* sub(size_t newstart, size_t newend) {
      if (newend - newstart > end - start) {
        // error?
      } else {
        std::vector<T> *newcontents = new std::vector<T>(contents.at(newstart), contents.at(newend));
        return new Slice(newend - newstart, newcontents);
      }
    }
    std::string string(); // use stringstream
  private:
    size_t start; 
    size_t end;
    std::vector<T> *contents;
  };

}

#endif