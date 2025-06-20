#include "Lexer.hpp"

class Parser {
  Lexer lexer;
  Token curToken;
  Token peekToken;

  public:
  Parser(Lexer lexer);
  bool checkToken(TokenType kind);
  bool checkPeek(TokenType kind);
  void match(TokenType kind);
  void nextToken();
  void abort(std::string message);
  bool isComparisonOperator();

  void program();
  void statement();
  void expression();
  void comparison();
  void term();
  void unary();
  void primary();
  void ident();
  void nl();
};