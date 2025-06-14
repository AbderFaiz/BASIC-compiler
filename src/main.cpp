#include <iostream>
#include "Lexer.hpp"


int main()
{
  std::string if_instr = "IF";
  std::string ident = "myvar";
  std::cout << token_name(END_OF_FILE) << std::endl;
  std::cout << token_name(token_type_from_name("NEWLINE")) << std::endl;
  std::cout << token_name(checkIfKeyword(if_instr)) << std::endl;
  std::cout << token_name(checkIfKeyword(ident)) << std::endl;
  return 0;
}