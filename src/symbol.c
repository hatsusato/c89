#include "symbol.h"

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
