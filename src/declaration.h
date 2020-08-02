#ifndef INCLUDE_GUARD_0DCFEB82_40C6_4B2A_A620_2FA21E8F81A8
#define INCLUDE_GUARD_0DCFEB82_40C6_4B2A_A620_2FA21E8F81A8

#include <stdio.h>

#include "typedef.h"

typedef enum { DECLARATION_FUNCTION } DeclarationTag;

Declaration *declaration_new_function(Function *);
void declaration_delete(Declaration *);
Declaration *declaration_build(Sexp *);
void declaration_print(FILE *, Declaration *);

#endif /* INCLUDE_GUARD_0DCFEB82_40C6_4B2A_A620_2FA21E8F81A8 */
