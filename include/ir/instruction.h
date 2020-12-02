#ifndef INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E
#define INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E

#include "ir/builder_type.h"

/* ret %1: (%1 -- ) */
void builder_instruction_ret(Builder *);
/* br label %1: (%1 -- ) */
void builder_instruction_br(Builder *);
/* br %1, label %2, label %3: (%1 %2 %3 -- ) */
void builder_instruction_br_cond(Builder *);
/* add %1, %2: (%1 %2 -- %0) */
void builder_instruction_add(Builder *);
/* alloca: ( -- %0)*/
void builder_instruction_alloca(Builder *, const char *);
/* load %1: (%1 -- %0) */
void builder_instruction_load(Builder *);
/* store %1, %2: (%1 %2 -- %0) */
void builder_instruction_store(Builder *);
/* icmp ne %1, %2: (%1 %2 -- %0) */
void builder_instruction_icmp_ne(Builder *);

#endif /* INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E */
