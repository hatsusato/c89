#ifndef INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E
#define INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E

#include "ir/block_type.h"
#include "ir/stack_type.h"
#include "ir/value_type.h"

/* ret %1 */
void stack_instruction_ret(Stack *, Value *);
/* br label %1 */
void stack_instruction_br(Stack *, Block *);
/* br %1, label %2, label %3 */
void stack_instruction_br_cond(Stack *, Value *, Block *, Block *);
/* switch %1, label % */
Value *stack_instruction_switch(Stack *, Value *);
void stack_instruction_switch_finish(Stack *, Value *);
/* [ %1, label %2 ... ] */
void stack_instruction_switch_case(Stack *, Value *, Value *);
/* add %1, %2 */
Value *stack_instruction_add(Stack *, Value *, Value *);
/* sub %1, %2 */
Value *stack_instruction_sub(Stack *, Value *, Value *);
/* load %1 */
Value *stack_instruction_load(Stack *, Value *);
/* store %1, %2 */
Value *stack_instruction_store(Stack *, Value *, Value *);
/* icmp ne %1, %2 */
Value *stack_instruction_icmp_ne(Stack *, Value *, Value *);

#endif /* INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E */
