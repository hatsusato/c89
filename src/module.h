#ifndef INCLUDE_GUARD_247AB52F_D89D_4924_960E_51BCF2BA3CCB
#define INCLUDE_GUARD_247AB52F_D89D_4924_960E_51BCF2BA3CCB

#include <stdio.h>

#include "typedef.h"

Module *module_new(void);
void module_delete(Module *);
void module_insert(Module *, Declaration *);
void module_build(Builder *, Sexp *);
void module_print(FILE *, Module *);

#endif /* INCLUDE_GUARD_247AB52F_D89D_4924_960E_51BCF2BA3CCB */
