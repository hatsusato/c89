#ifndef INCLUDE_GUARD_2066624D_9BD2_42A1_8E82_3B559F049976
#define INCLUDE_GUARD_2066624D_9BD2_42A1_8E82_3B559F049976

#include "ir/module_type.h"
#include "ir/value_type.h"

Module *module_new(void);
void module_delete(Module *);
void module_insert(Module *, Value *);

#endif /* INCLUDE_GUARD_2066624D_9BD2_42A1_8E82_3B559F049976 */
