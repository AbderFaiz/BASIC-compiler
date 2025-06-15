#include "Lexer.hpp"

Lexer::Lexer(std::string &source) : source(source + '\n'), curChar(' '), curPos(-1)
{
  nextChar();
};

void Lexer::nextChar()
{
  this->curPos += 1;
  if (this->curPos >= this->source.length())
    this->curChar = '\0';
  else
    this->curChar = this->source[this->curPos];
}

char Lexer::peek()
{
  if (this->curPos + 1 >= this->source.length())
    return '\0';
  return this->source[this->curPos + 1];
}

void Lexer::abort(std::string message)
{
  std::cout << "Lexing error: " << message << std::endl;
  exit(1);
}

void Lexer::skipWhitespace()
{
  while (this->curChar == ' ' ||
         this->curChar == '\t' ||
         this->curChar == '\r')
    nextChar();
}

void Lexer::skipComment()
{
  if (this->curChar == '#')
    while (this->curChar != '\n')
      nextChar();
}

Token Lexer::getToken()
{
  char lastChar;
  long unsigned int startPos;
  std::string tokText;
  Token res;

  skipWhitespace();
  skipComment();

  if (this->curChar == '+')
    res = Token(std::string(1, this->curChar), TokenType::PLUS);

  else if (this->curChar == '-')
    res = Token(std::string(1, this->curChar), TokenType::MINUS);

  else if (this->curChar == '*')
    res = Token(std::string(1, this->curChar), TokenType::ASTERISK);

  else if (this->curChar == '/')
    res = Token(std::string(1, this->curChar), TokenType::SLASH);

  else if (this->curChar == '=')
  {
    if (peek() == '=')
    {
      lastChar = this->curChar;
      nextChar();
      res = Token(std::string(1, lastChar) + this->curChar, TokenType::EQEQ);
    }
    else
    {
      res = Token(std::string(1, this->curChar), TokenType::EQ);
    }
  }

  else if (this->curChar == '>')
  {
    if (peek() == '=')
    {
      lastChar = this->curChar;
      nextChar();
      res = Token(std::string(1, lastChar) + this->curChar, TokenType::GTEQ);
    }
    else
    {
      res = Token(std::string(1, this->curChar), TokenType::GT);
    }
  }

  else if (this->curChar == '<')
  {
    if (peek() == '=')
    {
      lastChar = this->curChar;
      nextChar();
      res = Token(std::string(1, lastChar) + this->curChar, TokenType::LTEQ);
    }
    else
    {
      res = Token(std::string(1, this->curChar), TokenType::LT);
    }
  }

  else if (this->curChar == '!')
  {
    if (peek() == '=')
    {
      lastChar = this->curChar;
      nextChar();
      res = Token(std::string(1, lastChar) + this->curChar, TokenType::NOTEQ);
    }
    else
    {
      abort("Syntax Error: Expected !=, got !"+ std::string(1,peek()));
    }
  }

  else if (this->curChar == '\"'){
    nextChar();
    startPos = this->curPos;
    while (this->curChar != '\"')
      nextChar();
    tokText = this->source.substr(startPos, this->curPos - startPos);
    res = Token(tokText, TokenType::STRING);
  }

  else if (isdigit(this->curChar)){
    startPos = this->curPos;
    while (isdigit(peek()))
      nextChar();
    if (peek() == '.'){
      nextChar();
      while (isdigit(peek()))
        nextChar();
      if(isalpha(peek()))
        abort("Illegal character in number.");
    }
    else if(isalpha(peek()))
      abort("Illegal character in number.");
    tokText = this->source.substr(startPos, this->curPos - startPos + 1);
    res = Token(tokText, TokenType::NUMBER);
  }

  else if (isalpha(this->curChar)){
    startPos = this->curPos;
    while (isalnum(peek()))
      nextChar();
    tokText = this->source.substr(startPos, this->curPos - startPos + 1);
    res = Token(tokText, checkIfKeyword(tokText));
  }

  else if (this->curChar == '\n')
    res = Token(std::string(1, this->curChar), TokenType::NEWLINE);

  else if (this->curChar == '\0')
    res = Token(std::string(1, this->curChar), TokenType::END_OF_FILE);

  nextChar();
  return res;
}