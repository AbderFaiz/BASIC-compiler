#include "Lexer.hpp"

Lexer::Lexer(std::string source) : source(source + '\n'), curChar(' '), curPos(-1)
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
  std::cout << "Lexing error. " << message << std::endl;
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

    else if (this->curChar == '>')
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

    else if (this->curChar == '<')
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

  return res;
}