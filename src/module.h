#ifndef INCLUDE_GUARD_247AB52F_D89D_4924_960E_51BCF2BA3CCB
#define INCLUDE_GUARD_247AB52F_D89D_4924_960E_51BCF2BA3CCB

#include <stdio.h>

#include "typedef.h"

Module *module_new(void);
void module_delete(Module *);
Function *module_new_function(Module *);
void module_build(Module *, Sexp *);
void module_print(FILE *, Module *);

#endif /* INCLUDE_GUARD_247AB52F_D89D_4924_960E_51BCF2BA3CCB */
