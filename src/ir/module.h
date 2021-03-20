#ifndef INCLUDE_GUARD_2066624D_9BD2_42A1_8E82_3B559F049976
#define INCLUDE_GUARD_2066624D_9BD2_42A1_8E82_3B559F049976

#include "utility/types.h"

Module *module_new(void);
void module_delete(Module *);
Type *module_new_type(Module *, Type *);
Type *module_type_void(Module *);
Type *module_type_bool(Module *);
Type *module_type_int(Module *);
Type *module_type_pointer(Module *, Type *);
Type *module_type_label(Module *);
Type *module_find_type(Module *, Type *);
void module_insert_type(Module *, Type *);
void module_insert_value(Module *, Value *);
Global *module_new_global(Module *);
void module_insert_prior(Module *, Global *);
void module_build(Module *, Sexp *);
void module_pretty(Module *);

#endif /* INCLUDE_GUARD_2066624D_9BD2_42A1_8E82_3B559F049976 */
