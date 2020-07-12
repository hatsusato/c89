#ifndef INCLUDE_GUARD_F61F06FD_A1EC_40C7_BDE9_B15A87E95C41
#define INCLUDE_GUARD_F61F06FD_A1EC_40C7_BDE9_B15A87E95C41

#include "typedef.h"

struct struct_Symbol;
typedef struct struct_Symbol Symbol;

Symbol *symbol_new(const char *, Bool);
void symbol_delete(Symbol *);

#endif /* INCLUDE_GUARD_F61F06FD_A1EC_40C7_BDE9_B15A87E95C41 */
