#include "builder.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "ir/constant.h"
#include "ir/instruction.h"
#include "ir/pool.h"
#include "ir/register.h"
#include "ir/table.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"

struct struct_Builder {
  Vector *vec;
  Pool *pool;
  Table *table;
  Value *block;
  RegisterGenerator *gen;
};

static Value *builder_additive_expression(Builder *builder, Sexp *ast) {
  Value *value;
  assert(AST_ADDITIVE_EXPRESSION == sexp_get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 2)));
  assert(AST_PLUS == sexp_get_number(sexp_at(ast, 2)));
  value = builder_alloc_value(builder, VALUE_INSTRUCTION_ADD);
  value_insert(value, builder_expression(builder, sexp_at(ast, 1)));
  value_insert(value, builder_expression(builder, sexp_at(ast, 3)));
  return value;
}
static Value *builder_assignment_expression(Builder *builder, Sexp *ast) {
  Value *value, *lhsval, *rhsval;
  Sexp *lhs = sexp_at(ast, 1), *rhs = sexp_at(ast, 3);
  assert(AST_IDENTIFIER == sexp_get_tag(lhs));
  lhs = sexp_at(lhs, 1);
  assert(sexp_is_symbol(lhs));
  value = builder_alloc_value(builder, VALUE_INSTRUCTION_STORE);
  lhsval = table_find(builder->table, sexp_get_symbol(lhs));
  rhsval = builder_expression(builder, rhs);
  value_insert(value, rhsval);
  value_insert(value, lhsval);
  return value;
}
static Value *builder_jump_statement(Builder *builder, Sexp *ast) {
  Value *value;
  assert(AST_JUMP_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 2);
  value = builder_alloc_value(builder, VALUE_INSTRUCTION_RET);
  if (!sexp_is_nil(ast)) {
    value_insert(value, builder_expression(builder, ast));
  }
  return value;
}
static void builder_map_declaration(Sexp *ast, void *extra) {
  Builder *builder = extra;
  Value *instr;
  assert(AST_DECLARATION == sexp_get_tag(ast));
  ast = sexp_at(ast, 2);
  assert(AST_INIT_DECLARATOR_LIST == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(AST_INIT_DECLARATOR == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(AST_DECLARATOR == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(AST_DIRECT_DECLARATOR == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(AST_IDENTIFIER == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  instr = builder_alloc_value(builder, VALUE_INSTRUCTION_ALLOC);
  value_insert(builder->block, instr);
  table_insert(builder->table, sexp_get_symbol(ast), instr);
}
static void builder_declaration_list(Builder *builder, Sexp *ast) {
  assert(AST_DECLARATION_LIST == sexp_get_tag(ast));
  sexp_list_map(sexp_cdr(ast), builder, builder_map_declaration);
}
static void builder_map_statement(Sexp *ast, void *extra) {
  Builder *builder = extra;
  Value *value;
  assert(AST_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  switch (sexp_get_tag(ast)) {
  case AST_JUMP_STATEMENT:
    value = builder_jump_statement(builder, ast);
    value_insert(builder->block, value);
    break;
  case AST_EXPRESSION_STATEMENT:
    builder_expression(builder, sexp_at(ast, 1));
    break;
  default:
    assert(0);
    break;
  }
}
static void builder_statement_list(Builder *builder, Sexp *ast) {
  assert(AST_STATEMENT_LIST == sexp_get_tag(ast));
  sexp_list_map(sexp_cdr(ast), builder, builder_map_statement);
}
static void builder_function_definition(Builder *builder, Sexp *ast) {
  assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  assert(5 == sexp_length(ast));
  ast = sexp_at(ast, 4);
  assert(AST_COMPOUND_STATEMENT == sexp_get_tag(ast));
  builder_declaration_list(builder, sexp_at(ast, 2));
  builder_statement_list(builder, sexp_at(ast, 3));
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
  builder->table = table_new();
  builder->block = value_new(VALUE_BLOCK);
  builder->gen = register_generator_new();
  return builder;
}
void builder_delete(Builder *builder) {
  register_generator_delete(builder->gen);
  value_delete(builder->block);
  table_delete(builder->table);
  pool_delete(builder->pool);
  vector_delete(builder->vec);
  UTILITY_FREE(builder);
}
void builder_build(Builder *builder, Sexp *ast) {
  assert(AST_TRANSLATION_UNIT == sexp_get_tag(ast));
  sexp_list_map(sexp_cdr(ast), builder, builder_map_translation_unit);
  value_set_reg(builder->gen, builder->block);
  puts("target triple = \"x86_64-pc-linux-gnu\"\n");
  puts("define i32 @main() {");
  value_pretty(builder->block);
  puts("}");
}
Value *builder_expression(Builder *builder, Sexp *ast) {
  Value *value;
  switch (sexp_get_tag(ast)) {
  case AST_INTEGER_CONSTANT:
    return constant_new(builder->pool, ast);
  case AST_ADDITIVE_EXPRESSION:
    value = builder_additive_expression(builder, ast);
    value_insert(builder->block, value);
    return value;
  case AST_ASSIGNMENT_EXPRESSION:
    value = builder_assignment_expression(builder, ast);
    value_insert(builder->block, value);
    return value;
  case AST_IDENTIFIER:
    value = builder_alloc_value(builder, VALUE_INSTRUCTION_LOAD);
    value_insert(builder->block, value);
    value_insert(value,
                 table_find(builder->table, sexp_get_symbol(sexp_at(ast, 1))));
    return value;
  default:
    assert(0);
    return NULL;
  }
}
Value *builder_alloc_value(Builder *builder, ValueKind kind) {
  return pool_alloc(builder->pool, kind);
}
