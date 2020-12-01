#ifndef INCLUDE_GUARD_7E55B423_2396_4FF0_8B3A_C8FAFB3D11F3
#define INCLUDE_GUARD_7E55B423_2396_4FF0_8B3A_C8FAFB3D11F3

#include "ir/builder_type.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "sexp_type.h"
#include "types.h"

Bool builder_stack_empty(Builder *);
void builder_stack_push(Builder *, ValueKind);
void builder_stack_push_identifier(Builder *, Sexp *);
void builder_stack_init(Builder *, Sexp *);
Value *builder_stack_pop(Builder *);
Value *builder_stack_drop(Builder *);
Value *builder_stack_pop_insert(Builder *);
void builder_stack_insert(Builder *, Sexp *);
Value *builder_stack_top(Builder *);
void builder_stack_dup(Builder *);
void builder_stack_over(Builder *);
void builder_stack_swap(Builder *);
void builder_stack_rot(Builder *);
void builder_block_pop_set(Builder *);
void builder_ast(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_7E55B423_2396_4FF0_8B3A_C8FAFB3D11F3 */
