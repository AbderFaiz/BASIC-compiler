#include "Symbol.hpp"

Symbol::Symbol(const std::string id, SymbolKind k): txt(id), kind(k)
{
}

std::string Symbol::str() const{
  return this->txt;
}

SymbolKind Symbol::sym_kind() const{
  return this->kind;
}
