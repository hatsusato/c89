#ifndef INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E
#define INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E

#include "ir/block_type.h"
#include "ir/instruction_kind.h"
#include "ir/instruction_type.h"
#include "ir/stack_type.h"
#include "ir/value_type.h"
#include "types.h"

void stack_instruction_ret(Stack *, Value *);
void stack_instruction_br(Stack *, Block *);
void stack_instruction_br_cond(Stack *, Value *, Block *, Block *);
Instruction *stack_instruction_switch(Stack *, Value *);
void stack_instruction_switch_finish(Stack *, Instruction *);
void stack_instruction_switch_case(Stack *, Value *, Block *);
Instruction *stack_instruction_add(Stack *, Value *, Value *);
Instruction *stack_instruction_sub(Stack *, Value *, Value *);
Instruction *stack_instruction_alloca(Stack *, const char *);
Instruction *stack_instruction_load(Stack *, Value *);
Instruction *stack_instruction_store(Stack *, Value *, Value *);
Instruction *stack_instruction_icmp_ne(Stack *, Value *, Value *);

Instruction *instruction_new(InstructionKind);
void instruction_delete(Instruction *);
Bool instruction_is_terminator(Instruction *);
int instruction_set_id(Instruction *, int);
void instruction_print(Instruction *);
void instruction_pretty(Instruction *);

#endif /* INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E */
