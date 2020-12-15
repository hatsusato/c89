#ifndef INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E
#define INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E

#include "ir/pool_type.h"
#include "ir/stack_type.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "sexp_type.h"
#include "types.h"

typedef enum {
  STACK_NEXT_ALLOC,
  STACK_NEXT_BLOCK,
  STACK_NEXT_BREAK,
  STACK_NEXT_CONTINUE,
  STACK_NEXT_CURRENT,
  STACK_NEXT_DEFAULT,
  STACK_NEXT_RETURN,
  STACK_NEXT_SWITCH,
  STACK_NEXT_COUNT
} StackNextTag;

Stack *stack_new(Pool *, Sexp *);
void stack_delete(Stack *);
Value *stack_build(Stack *);

Value *stack_new_value(Stack *, ValueKind);
Value *stack_new_block(Stack *);
Value *stack_new_integer(Stack *, const char *);
Value *stack_label(Stack *, const char *);
Bool stack_last_terminator(Stack *);
void stack_load_from_symbol(Stack *, const char *);
void stack_store_to_symbol(Stack *, Value *, const char *);
Value *stack_alloca(Stack *, const char *);
Value *stack_find_alloca(Stack *, const char *);
void stack_jump_block(Stack *, Value *);
Value *stack_get_prev(Stack *);
Value *stack_set_prev(Stack *, Value *);
Value *stack_get_next(Stack *, StackNextTag);
Value *stack_set_next(Stack *, StackNextTag, Value *);
void stack_set_function_name(Stack *, const char *);
void stack_ast(Stack *, Sexp *);

#endif /* INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E */
