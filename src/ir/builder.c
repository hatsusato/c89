#include "builder.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "ir/block.h"
#include "ir/instruction.h"
#include "ir/register.h"
#include "ir/value.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"

struct struct_Builder {
  Vector *pool;
  Block *block;
  int reg, last;
};

static Value *builder_instruction(Builder *builder, Value *instr) {
  vector_push(builder->pool, instr);
  block_insert(builder->block, instr);
  return instr;
}
static Value *builder_integer_constant(Builder *builder, Sexp *ast) {
  Value *value = value_integer_constant(ast);
  vector_push(builder->pool, value);
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  builder->last = builder_fresh_id(builder);
  return value;
}
static Value *builder_additive_expression(Builder *builder, Sexp *ast) {
  Value *lhs, *rhs;
  assert(AST_ADDITIVE_EXPRESSION == sexp_get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 2)));
  assert(AST_PLUS == sexp_get_number(sexp_at(ast, 2)));
  lhs = builder_expression(builder, sexp_at(ast, 1));
  rhs = builder_expression(builder, sexp_at(ast, 3));
  builder->last = builder_fresh_id(builder);
  return builder_instruction(builder, instruction_binary(builder, lhs, rhs));
}
static void builder_jump_statement(Builder *builder, Sexp *ast) {
  Value *val = NULL;
  assert(AST_JUMP_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 2);
  if (sexp_is_nil(ast)) {
  } else {
    val = builder_expression(builder, ast);
  }
  builder_instruction(builder, instruction_ret(val));
}
static void builder_map_statement(Sexp *ast, void *builder) {
  assert(AST_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  switch (sexp_get_tag(ast)) {
  case AST_JUMP_STATEMENT:
    builder_jump_statement(builder, ast);
    break;
  default:
    assert(0);
    break;
  }
}
static void builder_function_definition(Builder *builder, Sexp *ast) {
  assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  assert(5 == sexp_length(ast));
  ast = sexp_at(ast, 4);
  assert(AST_COMPOUND_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 3);
  assert(AST_STATEMENT_LIST == sexp_get_tag(ast));
  sexp_list_map(sexp_cdr(ast), builder, builder_map_statement);
}
static void builder_map_translation_unit(Sexp *ast, void *builder) {
  switch (sexp_get_tag(ast)) {
  case AST_EXTERNAL_DECLARATION:
    break;
  case AST_FUNCTION_DEFINITION:
    builder_function_definition(builder, ast);
    break;
  default:
    assert(0);
    break;
  }
}

Builder *builder_new(void) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->pool = vector_new(utility_free);
  builder->block = block_new();
  builder->reg = builder->last = 0;
  return builder;
}
void builder_delete(Builder *builder) {
  block_delete(builder->block);
  vector_delete(builder->pool);
  UTILITY_FREE(builder);
}
void builder_build(Builder *builder, Sexp *ast) {
  assert(AST_TRANSLATION_UNIT == sexp_get_tag(ast));
  sexp_list_map(sexp_cdr(ast), builder, builder_map_translation_unit);
  block_set_id(builder, builder->block);
  puts("target triple = \"x86_64-pc-linux-gnu\"\n");
  puts("define i32 @main() {");
  block_print(builder->block);
  puts("}");
}
Value *builder_register(Builder *builder) {
  Value *reg = register_new();
  vector_push(builder->pool, reg);
  return reg;
}
Value *builder_expression(Builder *builder, Sexp *ast) {
  switch (sexp_get_tag(ast)) {
  case AST_INTEGER_CONSTANT:
    return builder_integer_constant(builder, ast);
  case AST_ADDITIVE_EXPRESSION:
    return builder_additive_expression(builder, ast);
  default:
    assert(0);
    return NULL;
  }
}
int builder_fresh_id(Builder *builder) {
  return builder->reg++;
}
