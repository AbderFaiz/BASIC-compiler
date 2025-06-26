#include <set>
#include "Lexer.hpp"
#include "Symbol.hpp"
#include "Emitter.hpp"


class Parser {
  Lexer lexer;
  Token curToken;
  Token peekToken;
  std::set<Symbol> symbols;
  Emitter* emitter;


  public:
  Parser(Lexer lexer, Emitter *emitter);
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
  void ident(SymbolKind k);
  void nl();
};