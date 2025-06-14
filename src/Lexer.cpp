#include "Lexer.hpp"

Lexer::Lexer():curChar(' '), curPos(-1){};

void Lexer::nextChar() {
  return;
}

void Lexer::peek() {
  return;
}

Token Lexer::getToken() {
  return Token("END_OF_FILE", END_OF_FILE);
}