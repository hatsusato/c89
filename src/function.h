#ifndef INCLUDE_GUARD_A4D0857A_3580_4AC6_B714_9A0637D15442
#define INCLUDE_GUARD_A4D0857A_3580_4AC6_B714_9A0637D15442

#include <stdio.h>

#include "typedef.h"

Function *function_new(void);
void function_delete(Function *);
void function_build(Module *, Sexp *);
void function_print(FILE *, Function *);

#endif /* INCLUDE_GUARD_A4D0857A_3580_4AC6_B714_9A0637D15442 */
