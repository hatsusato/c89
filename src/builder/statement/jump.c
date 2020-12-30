#include "jump.h"

#include "common.h"

static void builder_goto_statement(Builder *builder, Sexp *ast) {
  const char *label = identifier_symbol(sexp_at(ast, 2));
  Block *next = builder_label(builder, label);
  builder_instruction_br(builder, next);
}
static void builder_continue_statement(Builder *builder) {
  Block *next = builder_get_next(builder, BUILDER_NEXT_CONTINUE);
  builder_instruction_br(builder, next);
}
static void builder_break_statement(Builder *builder) {
  Block *next = builder_get_next(builder, BUILDER_NEXT_BREAK);
  if (!next) {
    next = builder_new_block(builder);
    builder_set_next(builder, BUILDER_NEXT_BREAK, next);
  }
  builder_instruction_br(builder, next);
}
static void builder_return_statement(Builder *builder, Sexp *ast) {
  Block *ret = builder_get_next(builder, BUILDER_NEXT_RETURN);
  Value *src;
  UTILITY_ASSERT(!sexp_is_nil(sexp_at(ast, 2)));
  builder_ast(builder, sexp_at(ast, 2));
  src = builder_get_value(builder);
  if (ret) {
    Value *dst = builder_get_retval(builder);
    builder_instruction_store(builder, src, dst);
    builder_instruction_br(builder, ret);
  } else {
    builder_instruction_ret(builder, src);
  }
}

void builder_jump_statement(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_JUMP_STATEMENT == sexp_get_tag(ast));
  switch (sexp_get_tag(sexp_at(ast, 1))) {
  case AST_GOTO:
    builder_goto_statement(builder, ast);
    break;
  case AST_CONTINUE:
    builder_continue_statement(builder);
    break;
  case AST_BREAK:
    builder_break_statement(builder);
    break;
  case AST_RETURN:
    builder_return_statement(builder, ast);
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
  builder_set_next(builder, BUILDER_NEXT_BLOCK, NULL);
}
