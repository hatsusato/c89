#include "symbol.h"

#include "set.h"
#include "utility.h"

typedef struct {
  const char *symbol;
  Bool flag;
} Symbol;

static Symbol *symbol_new(const char *symbol, Bool flag) {
  Symbol *ptr = UTILITY_MALLOC(Symbol);
  ptr->symbol = symbol;
  ptr->flag = flag;
  return ptr;
}
static void symbol_delete(Symbol *symbol) {
  UTILITY_FREE(symbol);
}
static int symbol_compare(const ElemType *lhs, const ElemType *rhs) {
  const Symbol *l = *lhs;
  const Symbol *r = *rhs;
  return utility_str_cmp(l->symbol, r->symbol);
}

Set *symbols_new(void) {
  Set *set = set_new((Destructor)symbol_delete, symbol_compare);
  return set;
}
void symbols_delete(Set *set) {
  set_delete(set);
}
