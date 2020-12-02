#ifndef INCLUDE_GUARD_7E55B423_2396_4FF0_8B3A_C8FAFB3D11F3
#define INCLUDE_GUARD_7E55B423_2396_4FF0_8B3A_C8FAFB3D11F3

#include "ir/stack_type.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "sexp_type.h"
#include "types.h"

Bool stack_multiple_return(Stack *);
Bool stack_empty(Stack *);
Value *stack_new_value(Stack *, ValueKind);
Value *stack_new_block(Stack *);
void stack_push_symbol(Stack *, const char *);
void stack_insert_symbol(Stack *, const char *);
void stack_set_symbol(Stack *, const char *);
void stack_register(Stack *);
Value *stack_push(Stack *, Value *);
void stack_add(Stack *, Value *);
Value *stack_pop(Stack *);
Value *stack_top(Stack *);
ValueKind stack_top_kind(Stack *);
void stack_set_next_block(Stack *, Value *);
Value *stack_get_next_block(Stack *);
void stack_change_flow(Stack *, Value *, Value *);
void stack_return(Stack *);
void stack_set_current_block(Stack *, Value *);
void stack_swap(Stack *);
void stack_ast(Stack *, Sexp *);

void stack_ret_init(Stack *);
Value *stack_ret(Stack *);

#endif /* INCLUDE_GUARD_7E55B423_2396_4FF0_8B3A_C8FAFB3D11F3 */
