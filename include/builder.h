#ifndef INCLUDE_GUARD_5D831CA9_8557_453C_9E51_10E9C0569E95
#define INCLUDE_GUARD_5D831CA9_8557_453C_9E51_10E9C0569E95

#include "builder_type.h"
#include "sexp_type.h"

Builder *builder_new(void);
void builder_delete(Builder *);
void builder_build(Builder *, Sexp *);
void builder_ast(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_5D831CA9_8557_453C_9E51_10E9C0569E95 */
