#ifndef INCLUDE_GUARD_F61F06FD_A1EC_40C7_BDE9_B15A87E95C41
#define INCLUDE_GUARD_F61F06FD_A1EC_40C7_BDE9_B15A87E95C41

#include "typedef.h"

struct struct_Symbol;
typedef struct struct_Symbol Symbol;

Symbol *symbol_new(Symbol *);
void symbol_delete(Symbol *);
int symbol_compare(const ElemType *, const ElemType *);
Set *symbol_set_new(void);
Bool symbol_flag(const Symbol *);
void symbol_register(Set *, const char *, Bool);
const Symbol *symbol_query(const Set *, const char *);

#endif /* INCLUDE_GUARD_F61F06FD_A1EC_40C7_BDE9_B15A87E95C41 */
