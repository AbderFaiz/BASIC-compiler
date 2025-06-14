#include <iostream>
#include "Lexer.hpp"


int main()
{
  std::string g = "IF";
  std::cout << token_name(END_OF_FILE) << std::endl;
  std::cout << token_name(token_type_from_name("NEWLINE")) << std::endl;
  return 0;
}