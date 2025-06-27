#include "Parser.hpp"

Parser::Parser(Lexer lexer, Emitter *emitter) : lexer(lexer), curToken(Token()), peekToken(Token()), symbols({}), emitter(emitter)
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
  // std::cout << "PROGRAM" << std::endl;
  this->emitter->headerLine("#include <stdio.h>");
  this->emitter->headerLine("int main(void){");
  while (checkToken(TokenType::NEWLINE))
  {
    nextToken();
  }
  while (!checkToken(TokenType::END_OF_FILE))
  {
    statement();
  }

  for (const Symbol &sym : this->symbols)
  {
    if (sym.sym_kind() == SymbolKind::LABEL_GOTOED)
    {
      Symbol label(sym.str(), SymbolKind::LABEL_DECLARATION);
      if (this->symbols.find(label) == this->symbols.end())
      {
        abort("GOTO to an undeclared label " + sym.str());
      }
    }
  }

  this->emitter->emitLine("return 0;");
  this->emitter->emitLine("}");

  for (const Symbol &sym : this->symbols)
  {
    if (sym.sym_kind() == SymbolKind::VARIABLE)
    {
      this->emitter->headerLine("float " + sym.str() + ";");
    }
  }
}

void Parser::statement()
{
  // "PRINT" (expression | string)
  if (checkToken(TokenType::PRINT))
  {
    // std::cout << "STATEMENT-PRINT" << std::endl;
    nextToken();

    if (checkToken(TokenType::STRING))
    {
      this->emitter->emitLine("printf(\"" + this->curToken.get_text() + "\\n\");");
      ;
      nextToken();
    }
    else
    {
      this->emitter->emit("printf(\"\%.2f\\n\", (float)(");
      expression();
      this->emitter->emitLine("));");
    }
  }

  // "IF" comparison "THEN" nl {statement} "ENDIF"
  else if (checkToken(TokenType::IF))
  {
    // std::cout << "STATEMENT-IF" << std::endl;
    nextToken();
    this->emitter->emit("if(");
    comparison();
    match(TokenType::THEN);
    nl();
    this->emitter->emitLine("){");
    while (!checkToken(TokenType::ENDIF))
    {
      statement();
    }
    match(TokenType::ENDIF);
    this->emitter->emitLine("}");
  }

  // "WHILE" comparison "REPEAT" nl {statement nl} "ENDWHILE"
  else if (checkToken(TokenType::WHILE))
  {
    // std::cout << "STATEMENT-WHILE" << std::endl;
    nextToken();
    this->emitter->emit("while(");
    comparison();
    match(TokenType::REPEAT);
    nl();
    this->emitter->emitLine("){");
    while (!checkToken(TokenType::ENDWHILE))
    {
      statement();
    }
    match(TokenType::ENDWHILE);
    this->emitter->emitLine("}");
  }

  // "LABEL" ident
  else if (checkToken(TokenType::LABEL))
  {
    // std::cout << "STATEMENT-LABEL" << std::endl;
    nextToken();
    ident(SymbolKind::LABEL_DECLARATION);
  }

  // "GOTO" ident
  else if (checkToken(TokenType::GOTO))
  {
    // std::cout << "STATEMENT-GOTO" << std::endl;
    nextToken();
    ident(SymbolKind::LABEL_GOTOED);
  }
  // "LET" ident "=" expression
  else if (checkToken(TokenType::LET))
  {
    // std::cout << "STATEMENT-ASSIGN" << std::endl;
    nextToken();
    ident(SymbolKind::VARIABLE);
    match(TokenType::EQ);
    this->emitter->emit(" = ");
    expression();
    this->emitter->emitLine(";");
  }
  // "INPUT" ident
  else if (checkToken(TokenType::INPUT))
  {
    // std::cout << "STATEMENT-INPUT" << std::endl;
    nextToken();
    this->emitter->emit("if (0 == scanf(\"\%f\", &");
    const std::string identext = this->curToken.get_text();
    ident(SymbolKind::VARIABLE);
    this->emitter->emitLine(")){");
    this->emitter->emitLine(identext + " = 0;");
    this->emitter->emitLine("scanf(\"\%*s\");\n}");
  }

  else
  {
    abort("Invalid statement at " + (this->curToken).get_text() + "(" + token_name((this->curToken).get_kind()) + ")");
  }

  nl();
}

void Parser::comparison()
{
  // std::cout << "COMPARISON" << std::endl;
  expression();
  if (isComparisonOperator())
  {
    this->emitter->emit(this->curToken.get_text());
    nextToken();
    expression();
  }
  else
  {
    abort("Expected comparison operator at: " + (this->curToken).get_text());
  }

  while (isComparisonOperator())
  {
    this->emitter->emit(this->curToken.get_text());
    nextToken();
    expression();
  }
}

void Parser::term()
{
  // std::cout << "TERM" << std::endl;
  unary();
  while (checkToken(TokenType::ASTERISK) || checkToken(TokenType::SLASH))
  {
    this->emitter->emit(this->curToken.get_text());
    nextToken();
    unary();
  }
}

void Parser::unary()
{
  // std::cout << "UNARY" << std::endl;
  if (checkToken(TokenType::PLUS) || checkToken(TokenType::MINUS))
  {
    this->emitter->emit(this->curToken.get_text());
    nextToken();
  }
  primary();
}

void Parser::primary()
{
  // std::cout << "PRIMARY" << " (" << (this->curToken).get_text() << ")" << std::endl;
  if (checkToken(TokenType::NUMBER))
  {
    this->emitter->emit(this->curToken.get_text());
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
    this->emitter->emit(identext);
    nextToken();
  }
  else
  {
    abort("Unexpected token at " + (this->curToken).get_text());
  }
}

void Parser::expression()
{
  // std::cout << "EXPRESSION" << std::endl;
  term();
  while (checkToken(TokenType::PLUS) || checkToken(TokenType::MINUS))
  {
    this->emitter->emit(this->curToken.get_text());
    nextToken();
    term();
  }
  //this->emitter->emitLine(";");
}

void Parser::ident(SymbolKind k)
{
  // std::cout << "IDENT" << std::endl;
  const std::string identText = this->curToken.get_text();
  match(TokenType::IDENT);
  Symbol curSymb(identText, k);
  switch (k)
  {
  case LABEL_DECLARATION:
    if (this->symbols.find(curSymb) != this->symbols.end())
      abort("Label already exists " + identText);
    this->symbols.insert(curSymb);
    this->emitter->emit(identText + ": ");
    break;
  case LABEL_GOTOED:
    this->symbols.insert(curSymb);
    this->emitter->emitLine("goto " + identText + ";");
    break;
  case VARIABLE:
    // std::cout << identText << std::endl;
    this->symbols.insert(curSymb);
    this->emitter->emit(identText);
    break;
  default:
    break;
  }
}

void Parser::nl()
{
  // std::cout << "NEWLINE" << std::endl;
  match(TokenType::NEWLINE);
  while (checkToken(TokenType::NEWLINE))
  {
    nextToken();
  }
}