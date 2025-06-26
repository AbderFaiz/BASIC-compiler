#include <iostream>
#include <fstream>
#include <sstream>
#include "Parser.hpp"

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
  Emitter* emitter = new Emitter("out.c");
  Parser myparser(mylexer, emitter);
  myparser.program();
  emitter->writeFile();
  delete emitter;
  return 0;
}