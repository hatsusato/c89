#ifndef INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E
#define INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E

#include "builder/types.h"
#include "module.h"
#include "sexp/types.h"

typedef enum {
  BUILDER_NEXT_ALLOC,
  BUILDER_NEXT_BLOCK,
  BUILDER_NEXT_BREAK,
  BUILDER_NEXT_CONTINUE,
  BUILDER_NEXT_CURRENT,
  BUILDER_NEXT_DEFAULT,
  BUILDER_NEXT_ENTRY,
  BUILDER_NEXT_RETURN,
  BUILDER_NEXT_SWITCH,
  BUILDER_NEXT_COUNT
} BuilderNextTag;

const char *identifier_symbol(Sexp *);
const char *integer_symbol(Sexp *);

Builder *builder_new(Module *);
void builder_delete(Builder *);
Block *builder_function_init(Builder *, Sexp *);
void builder_function_finish(Builder *);
Module *builder_get_module(Builder *);
Instruction *builder_get_retval(Builder *);
void builder_push_table(Builder *);
void builder_pop_table(Builder *);
void builder_init_global(Builder *, Global *, Sexp *);
Block *builder_label(Builder *, Sexp *);
void builder_insert_global(Builder *, Sexp *, Global *);
void builder_insert_local(Builder *, Sexp *, Instruction *);
Value *builder_find_identifier(Builder *, Sexp *);
void builder_jump_block(Builder *, Block *);
Block *builder_get_next(Builder *, BuilderNextTag);
Block *builder_set_next(Builder *, BuilderNextTag, Block *);
Value *builder_ast(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E */
