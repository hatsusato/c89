#ifndef INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E
#define INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E

#include "builder/type/spec.h"
#include "ir/module.h"

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

Builder *builder_new(Module *);
void builder_delete(Builder *);
void builder_init_next(Builder *, Function *);
void builder_init_return(Builder *);
void builder_finish_return(Builder *);
void builder_function_finish(Builder *);
void builder_push_table(Builder *);
void builder_pop_table(Builder *);
void builder_init_global(Builder *, Value *, Value *);
Block *builder_label(Builder *, const char *);
void builder_new_global(Builder *, const char *);
void builder_insert_global(Builder *, const char *, Global *);
void builder_insert_local(Builder *, const char *, Instruction *);
void builder_find_identifier(Builder *, const char *);
void builder_jump_block(Builder *, Block *);
Bool builder_is_local(Builder *);
void builder_cast(Builder *, Value *, Type *);
Module *builder_get_module(Builder *);
Value *builder_get_retval(Builder *);
Value *builder_get_value(Builder *);
void builder_set_value(Builder *, Value *);
void builder_new_integer(Builder *, const char *);
Type *builder_get_type(Builder *);
void builder_set_type(Builder *);
void builder_set_type_int(Builder *);
void builder_set_type_value(Builder *);
void builder_set_type_spec(Builder *, TypeSpecIndex);
void builder_reset_type_spec(Builder *);
Block *builder_get_next(Builder *, BuilderNextTag);
Block *builder_set_next(Builder *, BuilderNextTag, Block *);
void builder_ast_list(Builder *, Sexp *);
void builder_ast_map(Builder *, Sexp *);
void builder_ast(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E */
