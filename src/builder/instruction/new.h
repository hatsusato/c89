#ifndef INCLUDE_GUARD_81FFBAC4_2A19_466F_8734_2CF3E3E2913F
#define INCLUDE_GUARD_81FFBAC4_2A19_466F_8734_2CF3E3E2913F

#include "builder/types.h"

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

#endif /* INCLUDE_GUARD_81FFBAC4_2A19_466F_8734_2CF3E3E2913F */
