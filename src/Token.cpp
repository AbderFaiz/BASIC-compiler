#include "Token.hpp"

Token::Token(string tokenText, TokenType tokenKind):text(tokenText), kind(tokenKind) { }

TokenType checkIfKeyword(string &tokenText){
  TokenType token_type = token_type_from_name(tokenText);
  int token_value = static_cast<int>(token_type);
  if (100 < token_value && token_value < 200)
    return token_type;
  return TokenType::IDENT;
}