#include <string>
using std::string;

enum TokenType {
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
  GTEQ = 211,
  // UNKOWN
  UNKOWN = 999
};

string token_name(TokenType t) {
  switch (t) {
      case END_OF_FILE: return "END_OF_FILE";
      case NEWLINE: return "NEWLINE";
      case NUMBER: return "NUMBER";
      case IDENT: return "IDENT";
      case STRING: return "STRING";
      // Keywords
      case LABEL: return "LABEL";
      case GOTO: return "GOTO";
      case PRINT: return "PRINT";
      case INPUT: return "INPUT";
      case LET: return "LET";
      case IF: return "IF";
      case THEN: return "THEN";
      case ENDIF: return "ENDIF";
      case WHILE: return "WHILE";
      case REPEAT: return "REPEAT";
      case ENDWHILE: return "ENDWHILE";
      // Operators
      case EQ: return "EQ";
      case PLUS: return "PLUS";
      case MINUS: return "MINUS";
      case ASTERISK: return "ASTERISK";
      case SLASH: return "SLASH";
      case EQEQ: return "EQEQ";
      case NOTEQ: return "NOTEQ";
      case LT: return "LT";
      case LTEQ: return "LTEQ";
      case GT: return "GT";
      case GTEQ: return "GTEQ";
      default: return "UNKOWN";
  }
}

TokenType token_type_from_name(const string &name) {
  if (name == "END_OF_FILE") return END_OF_FILE;
  if (name == "NEWLINE") return NEWLINE;
  if (name == "NUMBER") return NUMBER;
  if (name == "IDENT") return IDENT;
  if (name == "STRING") return STRING;
  // Keywords
  if (name == "LABEL") return LABEL;
  if (name == "GOTO") return GOTO;
  if (name == "PRINT") return PRINT;
  if (name == "INPUT") return INPUT;
  if (name == "LET") return LET;
  if (name == "IF") return IF;
  if (name == "THEN") return THEN;
  if (name == "ENDIF") return ENDIF;
  if (name == "WHILE") return WHILE;
  if (name == "REPEAT") return REPEAT;
  if (name == "ENDWHILE") return ENDWHILE;
  // Operators
  if (name == "EQ") return EQ;
  if (name == "PLUS") return PLUS;
  if (name == "MINUS") return MINUS;
  if (name == "ASTERISK") return ASTERISK;
  if (name == "SLASH") return SLASH;
  if (name == "EQEQ") return EQEQ;
  if (name == "NOTEQ") return NOTEQ;
  if (name == "LT") return LT;
  if (name == "LTEQ") return LTEQ;
  if (name == "GT") return GT;
  if (name == "GTEQ") return GTEQ;
  return UNKOWN; // Default case for unknown names
}

TokenType checkIfKeyword(string &tokenText);

class Token{
  string text;
  TokenType kind;

  public:
  Token(string tokenText, TokenType tokenKind);
};