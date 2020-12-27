#ifndef INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E
#define INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E

#include "builder/types.h"

Instruction *instruction_new(void);
void instruction_delete(Instruction *);
Bool instruction_is_terminator(Instruction *);
int instruction_set_id(Instruction *, int);
void instruction_print(Instruction *);
void instruction_print_name(Instruction *);
void instruction_pretty(Instruction *);

void builder_instruction_ret(Builder *, Value *);
void builder_instruction_br(Builder *, Block *);
void builder_instruction_br_cond(Builder *, Value *, Block *, Block *);
void builder_instruction_switch(Builder *, Value *);
void builder_instruction_switch_finish(Builder *, Instruction *);
void builder_instruction_switch_case(Builder *, Value *, Block *);
void builder_instruction_add(Builder *, Value *, Value *);
void builder_instruction_sub(Builder *, Value *, Value *);
void builder_instruction_alloca(Builder *, const char *);
void builder_instruction_load(Builder *, Value *);
void builder_instruction_store(Builder *, Value *, Value *);
void builder_instruction_icmp_ne(Builder *, Value *, Value *);
Instruction *builder_new_local(Builder *);

#include "instruction/print.h"

#endif /* INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E */
