#ifndef INCLUDE_GUARD_F61F06FD_A1EC_40C7_BDE9_B15A87E95C41
#define INCLUDE_GUARD_F61F06FD_A1EC_40C7_BDE9_B15A87E95C41

#include "typedef.h"

typedef struct {
  const char *symbol;
  Bool flag;
} Symbol;

Symbol *symbol_new(const char *symbol, Bool flag);
void symbol_delete(Symbol *symbol);
int symbol_compare(const ElemType *, const ElemType *);
Bool symbol_flag(const Symbol *);
void symbol_register(Set *, Sexp *);
const Symbol *symbol_query(const Set *, const char *);

#endif /* INCLUDE_GUARD_F61F06FD_A1EC_40C7_BDE9_B15A87E95C41 */
