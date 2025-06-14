#include <iostream>
#include "Lexer.hpp"


std::string sample = "+-*/=+==><>=<=";

int main()
{
  Lexer mylexer(sample);
  Token t = mylexer.getToken();
  while(t.kind != UNKNOWN){
    std::cout << token_name(t.kind) << std::endl;
    t = mylexer.getToken();
  }
  return 0;
}