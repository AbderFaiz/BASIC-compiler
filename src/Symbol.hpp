#include <iostream>
#include <string>

enum SymbolKind {
  VARIABLE, LABEL_DECLARATION, LABEL_GOTOED
};


class Symbol{
  std::string txt;
  SymbolKind kind;

  public:
  Symbol(const std::string id, SymbolKind k);
  std::string str() const;
  SymbolKind sym_kind() const;
  bool operator<(const Symbol& other) const{
      return std::tie(this->txt,this->kind) < std::tie(other.txt, other.kind);
  }
};