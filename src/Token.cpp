#include "Token.hpp"


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
      default: return "UNKNOWN";
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
  return UNKNOWN; // Default case for unknown names
}

Token::Token():text("UNKNOWN"), kind(UNKNOWN){}
Token::Token(string tokenText, TokenType tokenKind):text(tokenText), kind(tokenKind) { }

/* Checks if a string is a keyword, 
   if it's the case returns the token associated
   if not returns an identifier token
*/
TokenType checkIfKeyword(string &tokenText){
  TokenType token_type = token_type_from_name(tokenText);
  int token_value = static_cast<int>(token_type);
  if (100 < token_value && token_value < 200)
    return token_type;
  return TokenType::IDENT;
}