#ifndef INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E
#define INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E

#include "ir/pool_type.h"
#include "ir/stack_type.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "sexp_type.h"
#include "types.h"

typedef enum {
  STACK_NEXT_BLOCK,
  STACK_NEXT_CURRENT,
  STACK_NEXT_COUNT
} StackNextTag;

Stack *stack_new(Pool *);
void stack_delete(Stack *);
Value *stack_build(Stack *, Sexp *);

Bool stack_empty(Stack *);
void stack_push(Stack *, Value *);
Value *stack_pop(Stack *);
Value *stack_new_value(Stack *, ValueKind);
Value *stack_new_block(Stack *);
void stack_push_integer(Stack *, const char *);
void stack_load_from_symbol(Stack *, const char *);
void stack_store_to_symbol(Stack *, const char *);
void stack_alloca(Stack *, const char *);
void stack_into_next_block(Stack *, Value *);
Bool stack_last_terminator(Stack *);
void stack_insert_to_block(Stack *);
void stack_insert_as_operand(Stack *, Value *);
Value *stack_get_default_block(Stack *);
Value *stack_get_return_block(Stack *);
Value *stack_get_switch_instruction(Stack *);
Value *stack_get_next(Stack *, StackNextTag);
Value *stack_set_next(Stack *, StackNextTag, Value *);
void stack_set_function_name(Stack *, const char *);
void stack_ast(Stack *, Sexp *);

#endif /* INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E */
