#ifndef INCLUDE_GUARD_2066624D_9BD2_42A1_8E82_3B559F049976
#define INCLUDE_GUARD_2066624D_9BD2_42A1_8E82_3B559F049976

#include "builder/types.h"
#include "sexp/types.h"

struct struct_Module;
typedef struct struct_Module Module;

Module *module_new(void);
void module_delete(Module *);
TypePool *module_get_type(Module *);
Type *module_find_type(Module *, Type *);
void module_insert_type(Module *, Type *);
Function *module_new_function(Module *);
Block *module_new_block(Module *);
Instruction *module_new_instruction(Module *);
Constant *module_new_constant(Module *);
Global *module_new_global(Module *);
void module_insert_prior(Module *, Global *);
void module_build(Module *, Sexp *);
void module_pretty(Module *);

#endif /* INCLUDE_GUARD_2066624D_9BD2_42A1_8E82_3B559F049976 */
