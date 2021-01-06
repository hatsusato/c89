#ifndef INCLUDE_GUARD_9CEF8276_25CA_4457_A042_1492E261359B
#define INCLUDE_GUARD_9CEF8276_25CA_4457_A042_1492E261359B

#include "builder/types.h"

Function *function_new(void);
void function_delete(Function *);
void function_insert(Function *, Block *);
Type *function_return_type(Function *);
void function_set_id(Function *);
void function_pretty(Function *);
int function_count_return(Sexp *);

Function *builder_new_function(Builder *, const char *, Sexp *);

#endif /* INCLUDE_GUARD_9CEF8276_25CA_4457_A042_1492E261359B */
