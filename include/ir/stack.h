#ifndef INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E
#define INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E

#include "ir/pool_type.h"
#include "ir/stack_type.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "sexp_type.h"

Stack *stack_new(Pool *);
void stack_delete(Stack *);
Value *stack_build(Stack *, Sexp *);

Value *stack_new_value(Stack *, ValueKind);
Value *stack_new_block(Stack *);
void stack_push_integer(Stack *, const char *);
void stack_push_symbol(Stack *, const char *);
void stack_insert_symbol(Stack *, const char *);
void stack_set_symbol(Stack *, const char *);
void stack_register(Stack *);
Value *stack_push(Stack *, Value *);
void stack_add(Stack *, Value *);
Value *stack_pop(Stack *);
Value *stack_top(Stack *);
ValueKind stack_top_kind(Stack *);
Value *stack_get_next_block(Stack *);
void stack_change_flow(Stack *, Value *, Value *);
void stack_return(Stack *);
void stack_swap(Stack *);

void stack_ret_init(Stack *);
Value *stack_ret(Stack *);
void stack_insert_allocs(Stack *);
void stack_set_function_name(Stack *, Sexp *);

#endif /* INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E */
