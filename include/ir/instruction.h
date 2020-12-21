#ifndef INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E
#define INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E

#include "builder_type.h"
#include "ir/block_type.h"
#include "ir/instruction_kind.h"
#include "ir/instruction_type.h"
#include "ir/value_type.h"
#include "types.h"

Instruction *instruction_new(void);
void instruction_delete(Instruction *);
Bool instruction_is_terminator(Instruction *);
int instruction_set_id(Instruction *, int);
void instruction_print(Instruction *);
void instruction_pretty(Instruction *);

Instruction *stack_new_instruction(Builder *, InstructionKind);
void stack_instruction_ret(Builder *, Value *);
void stack_instruction_br(Builder *, Block *);
void stack_instruction_br_cond(Builder *, Value *, Block *, Block *);
Instruction *stack_instruction_switch(Builder *, Value *);
void stack_instruction_switch_finish(Builder *, Instruction *);
void stack_instruction_switch_case(Builder *, Value *, Block *);
Instruction *stack_instruction_add(Builder *, Value *, Value *);
Instruction *stack_instruction_sub(Builder *, Value *, Value *);
Instruction *stack_instruction_alloca(Builder *, const char *);
Instruction *stack_instruction_load(Builder *, Value *);
Instruction *stack_instruction_store(Builder *, Value *, Value *);
Instruction *stack_instruction_icmp_ne(Builder *, Value *, Value *);

#endif /* INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E */
