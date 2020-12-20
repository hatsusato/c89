#ifndef INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E
#define INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E

#include "ir/block_type.h"
#include "ir/function_type.h"
#include "ir/instruction_kind.h"
#include "ir/instruction_type.h"
#include "ir/module_type.h"
#include "ir/stack_type.h"
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
  STACK_NEXT_ENTRY,
  STACK_NEXT_RETURN,
  STACK_NEXT_SWITCH,
  STACK_NEXT_COUNT
} StackNextTag;

Stack *stack_new(Module *);
void stack_delete(Stack *);
Module *stack_get_module(Stack *);
Function *stack_get_function(Stack *);
void stack_build(Stack *, Sexp *);
void stack_build_init(Stack *, Sexp *);
void stack_build_finish(Stack *);

Block *stack_label(Stack *, const char *);
Bool stack_last_terminator(Stack *);
void stack_alloca(Stack *, const char *, Instruction *);
Value *stack_find_alloca(Stack *, const char *);
void stack_jump_block(Stack *, Block *);
Block *stack_get_next(Stack *, StackNextTag);
Block *stack_set_next(Stack *, StackNextTag, Block *);
Value *stack_ast(Stack *, Sexp *);

#endif /* INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E */
