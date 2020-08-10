#ifndef INCLUDE_GUARD_B9CC5D68_6094_4DEA_88B4_20E85C99FEFC
#define INCLUDE_GUARD_B9CC5D68_6094_4DEA_88B4_20E85C99FEFC

#include "typedef.h"

Builder *builder_new(void);
void builder_new_module(Builder *);
Function *builder_new_function(Builder *);
void builder_delete(Builder *);
Module *builder_module(Builder *);
Function *builder_function(Builder *);

#endif /* INCLUDE_GUARD_B9CC5D68_6094_4DEA_88B4_20E85C99FEFC */
