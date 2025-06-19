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
  Token nextToken();
  void abort(std::string message);

  void program();
  void statement();
  void expression();
  void comparison();
  void ident();
  void nl();
};