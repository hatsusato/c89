#ifndef INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E
#define INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E

#include "ir/stack_type.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "sexp_type.h"

Stack *stack_new(void);
void stack_delete(Stack *);
void stack_build(Stack *, Sexp *);
void stack_print(Stack *);

#endif /* INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E */
