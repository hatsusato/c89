#ifndef INCLUDE_GUARD_2066624D_9BD2_42A1_8E82_3B559F049976
#define INCLUDE_GUARD_2066624D_9BD2_42A1_8E82_3B559F049976

#include "builder/block/type.h"
#include "builder/constant/type.h"
#include "builder/function/type.h"
#include "builder/instruction/type.h"
#include "builder/instruction_kind.h"
#include "builder/module/type.h"
#include "sexp_type.h"

Module *module_new(void);
void module_delete(Module *);
Function *module_new_function(Module *);
Block *module_new_block(Module *);
Instruction *module_new_instruction(Module *);
Constant *module_new_constant(Module *);
void module_build(Module *, Sexp *);
void module_pretty(Module *);

#endif /* INCLUDE_GUARD_2066624D_9BD2_42A1_8E82_3B559F049976 */
