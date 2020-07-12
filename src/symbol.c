#include "symbol.h"

#include "utility.h"

struct struct_Symbol {
  const char *symbol;
  Bool flag;
};

Symbol *symbol_new(const char *symbol, Bool flag) {
  Symbol *ptr = UTILITY_MALLOC(Symbol);
  ptr->symbol = symbol;
  ptr->flag = flag;
  return ptr;
}
void symbol_delete(Symbol *symbol) {
  UTILITY_FREE(symbol);
}
