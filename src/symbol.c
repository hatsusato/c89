#include "symbol.h"

#include "set.h"
#include "utility.h"

Symbol *symbol_new(const char *symbol, Bool flag) {
  Symbol *ptr = UTILITY_MALLOC(Symbol);
  ptr->symbol = symbol;
  ptr->flag = flag;
  return ptr;
}
void symbol_delete(Symbol *symbol) {
  UTILITY_FREE(symbol);
}
int symbol_compare(const ElemType *lhs, const ElemType *rhs) {
  const Symbol *l = *lhs;
  const Symbol *r = *rhs;
  return utility_str_cmp(l->symbol, r->symbol);
}
