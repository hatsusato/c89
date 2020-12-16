#ifndef INCLUDE_GUARD_9CEF8276_25CA_4457_A042_1492E261359B
#define INCLUDE_GUARD_9CEF8276_25CA_4457_A042_1492E261359B

#include "ir/function_type.h"
#include "ir/value_type.h"

Function *function_new(void);
void function_delete(Function *);
void function_insert(Function *, Value *);

#endif /* INCLUDE_GUARD_9CEF8276_25CA_4457_A042_1492E261359B */
