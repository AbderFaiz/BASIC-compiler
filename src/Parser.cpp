#include "Parser.hpp"

Parser::Parser(Lexer lexer) : lexer(lexer), curToken(Token()), peekToken(Token()), symbols({})
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

bool Parser::isComparisonOperator()
{
  return (checkToken(TokenType::GT) ||
          checkToken(TokenType::GTEQ) ||
          checkToken(TokenType::EQEQ) ||
          checkToken(TokenType::NOTEQ) ||
          checkToken(TokenType::LTEQ) ||
          checkToken(TokenType::LT));
}

void Parser::program()
{
  std::cout << "PROGRAM" << std::endl;
  while (checkToken(TokenType::NEWLINE))
  {
    nextToken();
  }
  while (!checkToken(TokenType::END_OF_FILE))
  {
    statement();
  }

  for (const Symbol& sym : this->symbols) {
    if (sym.sym_kind() == SymbolKind::LABEL_GOTOED){
      Symbol label(sym.str(), SymbolKind::LABEL_DECLARATION);
      if (this->symbols.find(label) == this->symbols.end()){
        abort ("GOTO to an undeclared label "+sym.str());
      }
    }
  }

  Symbol label("TOTO", SymbolKind::LABEL_DECLARATION);
  this->symbols.insert(label);
  this->symbols.insert(label);
  this->symbols.insert(label);
  std::cout << "*** SYMB TABLE ***" << std::endl;
  for (const Symbol& sym : this->symbols) {
        std::cout << sym.str() << "-" << sym.sym_kind() << std::endl;
  }
}

void Parser::statement()
{
  // "PRINT" (expression | string)
  if (checkToken(TokenType::PRINT))
  {
    std::cout << "STATEMENT-PRINT" << std::endl;
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
    std::cout << "STATEMENT-IF" << std::endl;
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
    std::cout << "STATEMENT-WHILE" << std::endl;
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
  else if (checkToken(TokenType::LABEL))
  {
    std::cout << "STATEMENT-LABEL" << std::endl;
    nextToken();
    ident(SymbolKind::LABEL_DECLARATION);
  }

  // "GOTO" ident
  else if (checkToken(TokenType::GOTO))
  {
    std::cout << "STATEMENT-GOTO" << std::endl;
    nextToken();
    ident(SymbolKind::LABEL_GOTOED);
  }
  // "LET" ident "=" expression
  else if (checkToken(TokenType::LET))
  {
    std::cout << "STATEMENT-ASSIGN" << std::endl;
    nextToken();
    ident(SymbolKind::VARIABLE);
    match(TokenType::EQ);
    expression();
  }
  // "INPUT" ident
  else if (checkToken(TokenType::INPUT))
  {
    std::cout << "STATEMENT-INPUT" << std::endl;
    nextToken();
    ident(SymbolKind::VARIABLE);
  }

  else
  {
    abort("Invalid statement at " + (this->curToken).get_text() + "(" + token_name((this->curToken).get_kind()) + ")");
  }

  nl();
}

void Parser::comparison()
{
  std::cout << "COMPARISON" << std::endl;
  expression();
  if (isComparisonOperator())
  {
    nextToken();
    expression();
  }
  else
  {
    abort("Expected comparison operator at: " + (this->curToken).get_text());
  }

  while (isComparisonOperator())
  {
    nextToken();
    expression();
  }
}

void Parser::term()
{
  std::cout << "TERM" << std::endl;
  unary();
  while (checkToken(TokenType::ASTERISK) || checkToken(TokenType::SLASH))
  {
    nextToken();
    unary();
  }
}

void Parser::unary()
{
  std::cout << "UNARY" << std::endl;
  if (checkToken(TokenType::PLUS) || checkToken(TokenType::MINUS))
  {
    nextToken();
  }
  primary();
}

void Parser::primary()
{
  std::cout << "PRIMARY" << " (" << (this->curToken).get_text() << ")" << std::endl;
  if (checkToken(TokenType::NUMBER))
  {
    nextToken();
  }
  else if (checkToken(TokenType::IDENT))
  {
    const std::string identext = this->curToken.get_text();
    Symbol tmp(identext, SymbolKind::VARIABLE);
    if (this->symbols.find(tmp) == this->symbols.end())
    {
      abort("Underclared variable " + this->curToken.get_text());
    }
    nextToken();
  }
  else
  {
    abort("Unexpected token at " + (this->curToken).get_text());
  }
}

void Parser::expression()
{
  std::cout << "EXPRESSION" << std::endl;
  term();
  while (checkToken(TokenType::PLUS) || checkToken(TokenType::MINUS))
  {
    nextToken();
    term();
  }
}

void Parser::ident(SymbolKind k)
{
  std::cout << "IDENT" << std::endl;
  const std::string identText = this->curToken.get_text();
  match(TokenType::IDENT);
  Symbol curSymb(identText, k);
  switch (k)
  {
  case LABEL_DECLARATION:
    if (this->symbols.find(curSymb) != this->symbols.end())
      abort("Label already exists " + identText);
    this->symbols.insert(curSymb);
    break;
  case LABEL_GOTOED:
    this->symbols.insert(curSymb);
    break;
  case VARIABLE:
    std::cout << identText << std::endl;
    this->symbols.insert(curSymb);
    break;
  default:
    break;
  }
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