#ifndef INCLUDE_GUARD_F61F06FD_A1EC_40C7_BDE9_B15A87E95C41
#define INCLUDE_GUARD_F61F06FD_A1EC_40C7_BDE9_B15A87E95C41

#include "typedef.h"

typedef Set SymbolSet;
struct struct_Symbol;
typedef struct struct_Symbol Symbol;

SymbolSet *symbol_set_new(void);
Bool symbol_flag(const Symbol *);
void symbol_register(SymbolSet *, const char *, Bool);
const Symbol *symbol_query(const SymbolSet *, const char *);

#endif /* INCLUDE_GUARD_F61F06FD_A1EC_40C7_BDE9_B15A87E95C41 */
