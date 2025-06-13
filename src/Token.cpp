#include "Token.hpp"

Token::Token(string tokenText, enum TokenType tokenKind){
  this->text = tokenText;
  this->kind = tokenKind;
}

Token::checkIfKeyword(string tokenText){
  
}