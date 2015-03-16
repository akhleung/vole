#include <cctype>
#include <iostream>
#include <cstdlib>
#include <string>
#include "slice.hpp"
#include "allocator.hpp"

using namespace std;


namespace Vole {

  class Parser {
    char* src;
    Allocator& alloc;

  public:
    Parser(char* c, Allocator& a) : src(c), alloc(a) { }
    Value parse();
    Value parse_vector();
  };

  Value Parser::parse() {
    cout << "parse: " << *src << endl;
    if (*src == '(') {
      src += 1;
      return parse_vector();
    } else if (*src == '#') {
      src += 1;
      if (*src == 't') {
        src += 1;
        return Value(true);
      } else if (*src == 'f') {
        src += 1;
        return Value(false);
      }
    } else if (isdigit(*src)) {
      int i = 1;
      char* dig = src;
      while (isdigit(*src) && !iscntrl(*src)) {
        i++;
        src += 1;
      }
      return Value(atoi(std::string(dig, i).c_str()));
    } else if (isspace(*src)) {
      src +=1;
    } else {
      // assuming identifier
      int i = 1;
      char* cp = src;
      while (!isspace(*src) && !iscntrl(*src)) {
        i++;
        src += 1;
      }
      string id = std::string(cp, i);
      cout << "id: " << id << endl;
      return Value(String(alloc, id));
    }
  }

  Value Parser::parse_vector() {
    cout << "parse_vector: " << *src << endl;
    Vector vect = Vector(alloc, {});
    while (*src != ')'  && !iscntrl(*src)) {
      Value v = parse();
      vect = append(alloc, vect, v);
      cout << "v: " << v << endl;
      cout << "vector: " << vect << endl;
    }
    src += 1;
    cout << " final vector: " << vect << endl;
    return Value(vect);
  }

}

using namespace Vole;
// using namespace std;

int main() {
  auto alloc = Allocator();
  auto p = Parser((char * )("(hello (one two (three) ) )"), alloc);
  Value result = p.parse();
  cout << result << endl;
}