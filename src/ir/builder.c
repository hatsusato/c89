#include "builder.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "ir/block.h"
#include "ir/constant.h"
#include "ir/instruction.h"
#include "ir/pool.h"
#include "ir/register.h"
#include "ir/value.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"

struct struct_Builder {
  Vector *vec;
  Pool *pool;
  Block *block;
  RegisterGenerator *gen;
};

static void builder_map_statement(Sexp *ast, void *extra) {
  Builder *builder = extra;
  Value *value;
  assert(AST_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  switch (sexp_get_tag(ast)) {
  case AST_JUMP_STATEMENT:
    value = instruction_build(builder, ast);
    block_insert(builder->block, value);
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
  builder->vec = vector_new(utility_free);
  builder->pool = pool_new();
  builder->block = block_new();
  builder->gen = register_generator_new();
  return builder;
}
void builder_delete(Builder *builder) {
  register_generator_delete(builder->gen);
  block_delete(builder->block);
  pool_delete(builder->pool);
  vector_delete(builder->vec);
  UTILITY_FREE(builder);
}
void builder_build(Builder *builder, Sexp *ast) {
  assert(AST_TRANSLATION_UNIT == sexp_get_tag(ast));
  sexp_list_map(sexp_cdr(ast), builder, builder_map_translation_unit);
  block_set_reg(builder->gen, builder->block);
  puts("target triple = \"x86_64-pc-linux-gnu\"\n");
  puts("define i32 @main() {");
  block_print(builder->block);
  puts("}");
}
Value *builder_expression(Builder *builder, Sexp *ast) {
  Value *value;
  switch (sexp_get_tag(ast)) {
  case AST_INTEGER_CONSTANT:
    return constant_new(builder->pool, ast);
  case AST_ADDITIVE_EXPRESSION:
    value = instruction_build(builder, ast);
    block_insert(builder->block, value);
    return value;
  default:
    assert(0);
    return NULL;
  }
}
Value *builder_alloc_value(Builder *builder, ValueKind kind) {
  return pool_alloc(builder->pool, kind);
}
