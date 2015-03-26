#ifndef MUNCHAR_TOKENS
#define MUNCHAR_TOKENS

#include "munchar.hpp"
#include <cctype>

namespace Munchar {
  namespace Tokens {
    // basic things
    constexpr auto _ = Any_Char { };
    constexpr auto newline = CHR('\n');
    constexpr auto spaces = CLS(" \t\r");

    // numbers
    constexpr auto digit = MUNCHAR_STATIC_PREDICATE(::isdigit);
    constexpr auto sign = CLS("+-");
    constexpr auto dot = CHR('.');
    constexpr auto integer = ~sign ^ +digit;
    constexpr auto number_no_exp = ~sign ^ ((*digit ^ dot ^ +digit) | +digit);
    constexpr auto number = number_no_exp ^ ~(CLS("eE") ^ ~sign ^ +digit);

    // identifiers
    constexpr auto letter = MUNCHAR_STATIC_PREDICATE(::isalpha);
    constexpr auto special_subsequent = CLS("+-.@");
    constexpr auto special_initial = CLS("!$%&*/:<=>?^_~");
    constexpr auto constituent = letter;
    constexpr auto initial = constituent | special_initial;
    constexpr auto subsequent = initial | digit | special_subsequent;
    constexpr auto peculiar_identifier
      = CLS("+-") | STR("...") | (STR("->") ^ *subsequent);
    constexpr auto identifier = (initial ^ *subsequent) | peculiar_identifier;

    // strings
    constexpr auto escape_seq = CHR('\\') ^ _;
    constexpr auto string
      = CHR('"') ^ *(escape_seq | (!CLS("\"\\") ^ _)) ^ CHR('"');

    // hash tags (special prefixes)
    constexpr auto hash_tag = CHR('#') ^ identifier;
    constexpr auto hash_paren = STR("#(");
    constexpr auto hash_comment = STR("#;");

    // boolean literals (technically hash tags)
    constexpr auto boolean = CHR('#') ^ CLS("tfTF") ^ !subsequent;

    // comments
    constexpr auto line_comment = CHR(';') ^ *(!newline ^ _) ^ ~newline;
  }
}

#endif