#ifndef INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E
#define INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E

#include "utility/types.h"

Instruction *instruction_new(void);
void instruction_delete(Instruction *);
Type *instruction_type(Instruction *);
int instruction_set_id(Instruction *, int);

#include "instruction/print.h"

#endif /* INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E */
