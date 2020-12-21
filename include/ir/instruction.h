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

Instruction *builder_new_instruction(Builder *, InstructionKind);
void builder_instruction_ret(Builder *, Value *);
void builder_instruction_br(Builder *, Block *);
void builder_instruction_br_cond(Builder *, Value *, Block *, Block *);
Instruction *builder_instruction_switch(Builder *, Value *);
void builder_instruction_switch_finish(Builder *, Instruction *);
void builder_instruction_switch_case(Builder *, Value *, Block *);
Instruction *builder_instruction_add(Builder *, Value *, Value *);
Instruction *builder_instruction_sub(Builder *, Value *, Value *);
Instruction *builder_instruction_alloca(Builder *, const char *);
Instruction *builder_instruction_load(Builder *, Value *);
Instruction *builder_instruction_store(Builder *, Value *, Value *);
Instruction *builder_instruction_icmp_ne(Builder *, Value *, Value *);

#endif /* INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E */
