#ifndef INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E
#define INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E

#include "builder/types.h"

Instruction *instruction_new(void);
void instruction_delete(Instruction *);
Bool instruction_is_terminator(Instruction *);
int instruction_set_id(Instruction *, int);

#include "instruction/new.h"
#include "instruction/print.h"

#endif /* INCLUDE_GUARD_87D09D26_5D7E_41DD_89F2_DCC79207182E */
