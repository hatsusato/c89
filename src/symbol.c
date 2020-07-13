#include "symbol.h"

#include "set.h"
#include "sexp.h"
#include "utility.h"

struct struct_Symbol {
  const char *symbol;
  Bool flag;
};

Symbol *symbol_new(Symbol *src) {
  Symbol *dst = UTILITY_MALLOC(Symbol);
  *dst = *src;
  return dst;
}
void symbol_delete(Symbol *symbol) {
  UTILITY_FREE(symbol);
}
int symbol_compare(const ElemType *lhs, const ElemType *rhs) {
  const Symbol *l = *lhs;
  const Symbol *r = *rhs;
  return utility_str_cmp(l->symbol, r->symbol);
}
Bool symbol_flag(const Symbol *symbol) {
  assert(symbol);
  return symbol->flag;
}

void symbol_register(Set *set, const char *identifier, Bool flag) {
  Symbol symbol;
  symbol.symbol = identifier;
  symbol.flag = flag;
  if (!set_contains(set, &symbol)) {
    set_insert(set, symbol_new(&symbol));
  }
}
const Symbol *symbol_query(const Set *set, const char *sym) {
  Symbol symbol;
  const ElemType *found;
  symbol.symbol = sym;
  symbol.flag = false;
  found = set_find(set, &symbol);
  return found ? *found : NULL;
}
