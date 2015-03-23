#include <cstdlib>
#include <string>
#include "tokenize.hpp"
#include "parser.hpp"
#include "context.hpp"

using namespace std;

namespace Vole {

  Value Parser::parse() {
    tokenize(src, tokens);
    return parse_value();
  }

  Value Parser::parse_value() {
    while (index < tokens.size()) {
      Lexeme cur = tokens[index];
      if (cur.type == Lexeme::Type::LPAREN) {
        ++index;
        return parse_list();
      } else if (cur.type == Lexeme::Type::BOOLEAN) {
        if (std::string(cur.beg, cur.end) == "#t") {
          ++index;
          return ctx.new_boolean(true);
        } else {
          ++index;
          return ctx.new_boolean(true);
        }
      } else if (cur.type == Lexeme::Type::NUMBER) {
        ++index;
        return ctx.new_number(atoi(std::string(cur.beg, cur.end).c_str()));
      } else if (cur.type == Lexeme::Type::IDENTIFIER) {
        ++index;
        return ctx.new_symbol(std::string(cur.beg, cur.end));
      } else {
        throw("unexpected lexeme type!");
      }
    }
    return Value();
  }

  Value Parser::parse_list() {
    vector<Value> vect;
    while (tokens[index].type != Lexeme::Type::RPAREN) {
      Value v = parse();
      vect.push_back(v);
    }
    ++index;
    return ctx.new_vector(vect);
  }

}