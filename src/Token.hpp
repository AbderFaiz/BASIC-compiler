#include <string>
using std::string;

enum class TokenType {
  END_OF_FILE = -1,
  NEWLINE = 0,
  NUMBER = 1,
  IDENT = 2,
  STRING = 3,
  //Keywords.
  LABEL = 101,
  GOTO = 102,
  PRINT = 103,
  INPUT = 104,
  LET = 105,
  IF = 106,
  THEN = 107,
  ENDIF = 108,
  WHILE = 109,
  REPEAT = 110,
  ENDWHILE = 111,
  //Operators
  EQ = 201,
  PLUS = 202,
  MINUS = 203,
  ASTERISK = 204,
  SLASH = 205,
  EQEQ = 206,
  NOTEQ = 207,
  LT = 208,
  LTEQ = 209,
  GT = 210,
  GTEQ = 211
};

string token_name(TokenType t) {
  switch (t) {
      case TokenType::END_OF_FILE: return "END_OF_FILE";
      case TokenType::NEWLINE: return "NEWLINE";
      case TokenType::NUMBER: return "NUMBER";
      case TokenType::IDENT: return "IDENT";
      case TokenType::STRING: return "STRING";
      // Keywords
      case TokenType::LABEL: return "LABEL";
      case TokenType::GOTO: return "GOTO";
      case TokenType::PRINT: return "PRINT";
      case TokenType::INPUT: return "INPUT";
      case TokenType::LET: return "LET";
      case TokenType::IF: return "IF";
      case TokenType::THEN: return "THEN";
      case TokenType::ENDIF: return "ENDIF";
      case TokenType::WHILE: return "WHILE";
      case TokenType::REPEAT: return "REPEAT";
      case TokenType::ENDWHILE: return "ENDWHILE";
      // Operators
      case TokenType::EQ: return "EQ";
      case TokenType::PLUS: return "PLUS";
      case TokenType::MINUS: return "MINUS";
      case TokenType::ASTERISK: return "ASTERISK";
      case TokenType::SLASH: return "SLASH";
      case TokenType::EQEQ: return "EQEQ";
      case TokenType::NOTEQ: return "NOTEQ";
      case TokenType::LT: return "LT";
      case TokenType::LTEQ: return "LTEQ";
      case TokenType::GT: return "GT";
      case TokenType::GTEQ: return "GTEQ";
      default: return "Unknown";
  }
}

class Token{
  string text;
  enum TokenType kind;

  public:
  Token(string tokenText, enum TokenType tokenKind);
  static enum TokenType checkIfKeyword(string tokenText);
};