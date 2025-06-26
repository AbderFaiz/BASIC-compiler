#include "Emitter.hpp"

Emitter::Emitter(std::string path) : fullpath(path), header(""), code("") {}

void Emitter::emit(std::string code)
{
  this->code += code;
}

void Emitter::emitLine(std::string code)
{
  this->code += code + '\n';
}

void Emitter::headerLine(std::string code)
{
  this->header += code + '\n';
  // std::cout << code << std::endl;
  // std::cout << this->header;
}

void Emitter::writeFile()
{
  std::ofstream outputFile(this->fullpath);
  if (outputFile.is_open())
  {
    // std::cout << this->header + this->code << std::endl;
    outputFile << this->header + this->code;
    outputFile.close();
  }
  else
  {
    // Handle error
    std::cerr << "Failed to open file: " << this->fullpath << std::endl;
  }
}