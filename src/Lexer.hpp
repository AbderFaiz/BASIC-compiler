#include <iostream>
#include "Token.hpp"

class Lexer{
  std::string source;
  char curChar;
  long unsigned int curPos;

  public:
  Lexer(std::string source);
  void nextChar();
  char peek();
  void abort(std::string message);
  void skipWhitespace();
  void skipComment();
  Token getToken();

};

