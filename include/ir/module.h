#ifndef INCLUDE_GUARD_2066624D_9BD2_42A1_8E82_3B559F049976
#define INCLUDE_GUARD_2066624D_9BD2_42A1_8E82_3B559F049976

#include "ir/block_type.h"
#include "ir/constant_type.h"
#include "ir/function_type.h"
#include "ir/instruction_kind.h"
#include "ir/instruction_type.h"
#include "ir/module_type.h"

Module *module_new(void);
void module_delete(Module *);
Function *module_new_function(Module *);
Block *module_new_block(Module *);
Instruction *module_new_instruction(Module *);
Constant *module_new_constant(Module *);
void module_pretty(Module *);

#endif /* INCLUDE_GUARD_2066624D_9BD2_42A1_8E82_3B559F049976 */
