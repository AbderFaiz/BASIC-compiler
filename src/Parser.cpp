#include "Parser.hpp"

Parser::Parser(Lexer lexer) : lexer(lexer), curToken(Token()), peekToken(Token())
{
  nextToken();
  nextToken();
}
bool Parser::checkToken(TokenType kind)
{
  return kind == (this->curToken).get_kind();
}
bool Parser::checkPeek(TokenType kind)
{
  return kind == (this->peekToken).get_kind();
}
void Parser::match(TokenType kind)
{
  if (!checkToken(kind))
  {
    abort("Expected " + token_name(kind) + ", got " + token_name((this->curToken).get_kind()));
  }
  nextToken();
}

void Parser::nextToken()
{
  this->curToken = this->peekToken;
  this->peekToken = (this->lexer).getToken();
}

void Parser::abort(std::string message)
{
  std::cout << "Error: " << message << std::endl;
  exit(1);
}

bool Parser::isComparisonOperator(){
  return (checkToken(TokenType::GT)   || 
          checkToken(TokenType::GTEQ) ||
          checkToken(TokenType::EQEQ) ||
          checkToken(TokenType::NOTEQ)||
          checkToken(TokenType::LTEQ) ||
          checkToken(TokenType::LT)
        );
}

void Parser::program()
{
  std::cout << "PROGRAM" << std::endl;
  while (checkToken(TokenType::NEWLINE)){
    nextToken();
  }
  while (!checkToken(TokenType::END_OF_FILE))
  {
    statement();
  }
}

void Parser::statement()
{
  std::cout << "STATEMENT" << std::endl;
  // "PRINT" (expression | string)
  if (checkToken(TokenType::PRINT))
  {
    nextToken();

    if (checkToken(TokenType::STRING))
    {
      nextToken();
    }
    else
    {
      expression();
    }
  }

  // "IF" comparison "THEN" nl {statement} "ENDIF"
  else if (checkToken(TokenType::IF))
  {
    nextToken();
    comparison();
    match(TokenType::THEN);
    nl();
    while (!checkToken(TokenType::ENDIF))
    {
      statement();
    }
    match(TokenType::ENDIF);
  }

  // "WHILE" comparison "REPEAT" nl {statement nl} "ENDWHILE"
  else if (checkToken(TokenType::WHILE))
  {
    nextToken();
    comparison();
    match(TokenType::REPEAT);
    nl();
    while (!checkToken(TokenType::ENDWHILE))
    {
      statement();
    }
    match(TokenType::ENDWHILE);
  }

  // "LABEL" ident
  else if (checkToken(TokenType::LABEL)){
    nextToken();
    ident();
  }

  // "GOTO" ident
  else if (checkToken(TokenType::GOTO)){
    nextToken();
    ident();
  }
  // "LET" ident "=" expression
  else if (checkToken(TokenType::LET)){
    nextToken();
    ident();
    match(TokenType::EQ);
    expression();
  }
  // "INPUT" ident
  else if (checkToken(TokenType::INPUT)){
    nextToken();
    ident();
  }

  else{
    abort("Invalid statement at "+ (this->curToken).get_text() + "(" + token_name((this->curToken).get_kind()) + ")");
  }

  nl();
}

void Parser::comparison()
{
  std::cout << "COMPARISON" << std::endl;
  expression();
  if (isComparisonOperator()){
    nextToken();
    expression();
  }
  else {
    abort("Expected comparison operator at: "+(this->curToken).get_text());
  }

  while (isComparisonOperator()){
    nextToken();
    expression();
  }
}

void Parser::term(){
  std::cout << "TERM" << std::endl;
  unary();
  while(checkToken(TokenType::ASTERISK) || checkToken(TokenType::SLASH)){
    nextToken();
    unary();
  }
}

void Parser::unary(){
  std::cout << "UNARY" << std::endl;
  if(checkToken(TokenType::PLUS) || checkToken(TokenType::MINUS)){
    nextToken();
  }
  primary();
}

void Parser::primary(){
  std::cout << "PRIMARY" << " (" << (this->curToken).get_text() << ")"<< std::endl;
  if(checkToken(TokenType::NUMBER)){
    nextToken();
  }
  else if(checkToken(TokenType::IDENT)){
    nextToken();
  }
  else{
    abort("Unexpected token at "+ (this->curToken).get_text());
  }
}

void Parser::expression()
{
  std::cout << "EXPRESSION" << std::endl;
  term();
  while(checkToken(TokenType::PLUS) || checkToken(TokenType::MINUS)){
    nextToken();
    term();
  }
}

void Parser::ident()
{
  std::cout << "IDENT" << std::endl;
  match(TokenType::IDENT);
}

void Parser::nl()
{
  std::cout << "NEWLINE" << std::endl;
  match(TokenType::NEWLINE);
  while (checkToken(TokenType::NEWLINE))
  {
    nextToken();
  }
}