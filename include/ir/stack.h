#ifndef INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E
#define INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E

#include "builder_type.h"
#include "ir/block_type.h"
#include "ir/function_type.h"
#include "ir/instruction_kind.h"
#include "ir/instruction_type.h"
#include "ir/module_type.h"
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

Builder *stack_new(Module *);
void stack_delete(Builder *);
void stack_function_init(Builder *, Function *);
void stack_function_finish(Builder *);
Module *stack_get_module(Builder *);
Block *stack_label(Builder *, const char *);
Bool stack_last_terminator(Builder *);
void stack_alloca(Builder *, const char *, Instruction *);
Value *stack_find_alloca(Builder *, const char *);
void stack_jump_block(Builder *, Block *);
Block *stack_get_next(Builder *, StackNextTag);
Block *stack_set_next(Builder *, StackNextTag, Block *);
Value *stack_ast(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E */
