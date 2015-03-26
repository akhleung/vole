#include <cstdlib>
#include <string>
#include "tokenize.hpp"
#include "parser.hpp"
#include "context.hpp"

using namespace std;

namespace Vole {

  Parser::Parser(const char* s, Context& c)
  : src(s), ctx(c), tokens(std::vector<Lexeme>()), index(0) 
  { }

  Value Parser::parse() {
    tokenize(src, 1, tokens);
    return parse_value();
  }

  Value Parser::parse_value() {
    while (index < tokens.size()) {
      Lexeme cur = tokens[index];
      switch (cur.type) {
        case Lexeme::Type::LPAREN: {
          return parse_vector();
        } break;
        case Lexeme::Type::BOOLEAN: {
          ++index;
          return ctx.new_boolean(cur.text == "#t");
        } break;
        case Lexeme::Type::NUMBER: {
          ++index;
          return ctx.new_number(atof(cur.text.c_str()));
        } break;
        case Lexeme::Type::IDENTIFIER: {
          ++index;
          return ctx.new_symbol(cur.text);
        } break;
        case Lexeme::Type::STRING: {
          ++index;
          return ctx.new_string(cur.text);
        } break;
        default: {
          throw("unexpected lexeme type!");
        }
      }
    }
    return Value();
  }

  Value Parser::parse_vector() {
    // pop left paren
    ++index;
    vector<Value> vec;
    while (tokens[index].type != Lexeme::Type::RPAREN) {
      Value v = parse_value();
      vec.push_back(v);
    }
    // pop right paren
    ++index;
    return ctx.new_vector(vec);
  }

}