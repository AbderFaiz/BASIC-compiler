#include "Token.hpp"

class Lexer{
  char curChar;
  int curPos;

  public:
  Lexer();
  void nextChar();
  void peek();
  Token getToken();

};

