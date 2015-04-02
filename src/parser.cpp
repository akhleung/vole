#include "parser.hpp"
#include "tokenize.hpp"
#include "context.hpp"
#include <cstdlib>

using namespace std;

namespace Vole {

  Parser::Parser(const char* s, Context& c)
  : src(s), ctx(c), tokens(std::vector<Lexeme>()), index(0) 
  { }

  Value Parser::parse() {
    tokenize(src, tokens, 1);
    return parse_value();
  }

  Value Parser::parse_value() {
    while (index < tokens.size()) {
      Lexeme cur = tokens[index];
      switch (cur.type) {
        case Lexeme::LPAREN: {
          return parse_vector();
        } break;
        case Lexeme::RPAREN: {
          throw "unmatched right-parenthesis";
        } break;
        case Lexeme::BOOLEAN: {
          ++index;
          return ctx.new_boolean((cur.text == "#t") | (cur.text == "#T"));
        } break;
        case Lexeme::NUMBER: {
          ++index;
          return ctx.new_number(atof(cur.text.c_str()));
        } break;
        case Lexeme::IDENTIFIER: {
          ++index;
          return ctx.new_symbol(cur.text);
        } break;
        case Lexeme::STRING: {
          ++index;
          return ctx.new_string(cur.text);
        } break;
        case Lexeme::QUOTE: {
          ++index;
          return ctx.new_vector({ ctx.new_symbol("quote"), parse_value() });
        } break;
        case Lexeme::COMMENT: {
          ++index;
          parse_value(); // discard the next value
        } break;
        default: {
          throw "unexpected token";
        }
      }
    }
    return Value();
  }

  Value Parser::parse_vector() {
    // pop left paren
    ++index;
    vector<Value> vec;
    while (tokens[index].type != Lexeme::RPAREN) {
      if (tokens[index].type == Lexeme::EOI) {
        throw "unterminated parenthesized expression";
      }
      Value v = parse_value();
      vec.push_back(v);
    }
    // pop right paren
    ++index;
    return ctx.new_vector(vec);
  }

}