#include <iostream>
#include <fstream>
#include <string>

class Emitter{
  std::string fullpath;
  std::string header;
  std::string code;

  public:
  Emitter(std::string path);
  void emit(std::string code);
  void emitLine(std::string code);
  void headerLine(std::string code);
  void writeFile();
};