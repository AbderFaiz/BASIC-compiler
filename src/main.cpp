#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.hpp"

int main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <file>\n";
    return 1;
  }

  std::ifstream file(argv[1]);

  if (!file) {
    std::cerr << "Error: couldn't open file " << argv[1] << "\n";
    return 1;
  }

  std::ostringstream ss;
  ss << file.rdbuf();
  std::string source = ss.str();

  Lexer mylexer(source);
  Token t = mylexer.getToken();
  while(t.get_kind() != END_OF_FILE){
    std::cout << token_name(t.get_kind()) << ": " << t.get_text() << std::endl;
    t = mylexer.getToken();
  }
  return 0;
}