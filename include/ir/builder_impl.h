#ifndef INCLUDE_GUARD_7E55B423_2396_4FF0_8B3A_C8FAFB3D11F3
#define INCLUDE_GUARD_7E55B423_2396_4FF0_8B3A_C8FAFB3D11F3

#include "ir/builder_type.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "sexp_type.h"
#include "types.h"

Bool builder_stack_empty(Builder *);
Value *builder_stack_new_value(Builder *, ValueKind);
void builder_stack_push_identifier(Builder *, Sexp *);
void builder_stack_init(Builder *, Sexp *);
void builder_stack_register(Builder *);
Value *builder_stack_pop(Builder *);
void builder_stack_insert(Builder *);
void builder_stack_insert_symbol(Builder *, const char *);
void builder_stack_pop_insert(Builder *);
ValueKind builder_stack_top_kind(Builder *);
void builder_stack_pop_block(Builder *);
void builder_stack_dup(Builder *);
void builder_stack_swap(Builder *);
void builder_ast(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_7E55B423_2396_4FF0_8B3A_C8FAFB3D11F3 */
