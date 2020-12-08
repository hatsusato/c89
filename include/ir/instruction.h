#ifndef INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E
#define INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E

#include "ir/stack_type.h"
#include "ir/value_type.h"

/* ret %1: (%1 -- ) */
void stack_instruction_ret(Stack *);
/* br label %1: ( -- ) */
void stack_instruction_br(Stack *, Value *);
/* br %1, label %2, label %3: (%1 -- ) */
void stack_instruction_br_cond(Stack *, Value *, Value *);
/* switch %1, label %2: (%1 %2 -- ) */
void stack_instruction_switch(Stack *);
/* [ %1, label %2 ... ]: (%1 %2 -- ) */
void stack_instruction_switch_case(Stack *);
/* add %1, %2: (%1 %2 -- %0) */
void stack_instruction_add(Stack *);
/* load %1: (%1 -- %0) */
void stack_instruction_load(Stack *);
/* store %1, %2: (%1 %2 -- %0) */
void stack_instruction_store(Stack *);
/* icmp ne %1, %2: (%1 %2 -- %0) */
void stack_instruction_icmp_ne(Stack *);

#endif /* INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E */
