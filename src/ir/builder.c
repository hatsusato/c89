#include "builder.h"

#include <stdio.h>

#include "ast/ast_tag.h"
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
  Vector *stack;
  Value *block;
  RegisterGenerator *gen;
};

static Value *builder_ast_map(Builder *builder, Sexp *ast,
                              Value *(*map)(Builder *, Sexp *)) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    map(builder, sexp_car(ast));
  }
  return NULL;
}
static Value *builder_integer_constant(Builder *builder, Sexp *ast) {
  Value *value;
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  value = builder_alloc_value(builder, VALUE_INTEGER_CONSTANT);
  value_set_value(value, sexp_get_symbol(ast));
  return value;
}
static Value *builder_identifier(Builder *builder, Sexp *ast) {
  Value *value;
  assert(AST_IDENTIFIER == sexp_get_tag(ast));
  value = builder_alloc_value(builder, VALUE_INSTRUCTION_LOAD);
  value_insert(value, table_find(builder->table, ast));
  value_insert(builder->block, value);
  return value;
}
static Value *builder_additive_expression(Builder *builder, Sexp *ast) {
  Value *value;
  assert(AST_ADDITIVE_EXPRESSION == sexp_get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 2)));
  assert(AST_PLUS == sexp_get_number(sexp_at(ast, 2)));
  value = builder_alloc_value(builder, VALUE_INSTRUCTION_ADD);
  value_insert(value, builder_expression(builder, sexp_at(ast, 1)));
  value_insert(value, builder_expression(builder, sexp_at(ast, 3)));
  value_insert(builder->block, value);
  return value;
}
static Value *builder_assignment_expression(Builder *builder, Sexp *ast) {
  Value *value;
  assert(AST_IDENTIFIER == sexp_get_tag(sexp_at(ast, 1)));
  value = builder_alloc_value(builder, VALUE_INSTRUCTION_STORE);
  value_insert(value, builder_expression(builder, sexp_at(ast, 3)));
  value_insert(value, table_find(builder->table, sexp_at(ast, 1)));
  value_insert(builder->block, value);
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
  value_insert(builder->block, value);
  return value;
}
static Value *builder_declaration(Builder *builder, Sexp *ast) {
  Value *value;
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
  value = builder_alloc_value(builder, VALUE_INSTRUCTION_ALLOC);
  table_insert(builder->table, ast, value);
  value_insert(builder->block, value);
  return value;
}
static Value *builder_expression_statement(Builder *builder, Sexp *ast) {
  assert(AST_EXPRESSION_STATEMENT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  if (!sexp_is_nil(ast)) {
    return builder_expression(builder, ast);
  }
  return NULL;
}
static Value *builder_statement(Builder *builder, Sexp *ast) {
  assert(AST_STATEMENT == sexp_get_tag(ast));
  return builder_expression(builder, sexp_at(ast, 1));
}
static Value *builder_compound_statement(Builder *builder, Sexp *ast) {
  assert(AST_COMPOUND_STATEMENT == sexp_get_tag(ast));
  builder_expression(builder, sexp_at(ast, 2));
  builder_expression(builder, sexp_at(ast, 3));
  return NULL;
}
static Value *builder_function_definition(Builder *builder, Sexp *ast) {
  assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  assert(5 == sexp_length(ast));
  return builder_expression(builder, sexp_at(ast, 4));
}
static void builder_stack_push(Builder *builder, Value *value) {
  vector_push(builder->stack, value);
}
static Value *builder_stack_pop(Builder *builder) {
  Value *value = vector_back(builder->stack);
  vector_pop(builder->stack);
  return value;
}

Builder *builder_new(void) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->vec = vector_new(utility_free);
  builder->pool = pool_new();
  builder->table = table_new();
  builder->stack = vector_new(NULL);
  builder->block = value_new(VALUE_BLOCK);
  builder->gen = register_generator_new();
  return builder;
}
void builder_delete(Builder *builder) {
  register_generator_delete(builder->gen);
  value_delete(builder->block);
  vector_delete(builder->stack);
  table_delete(builder->table);
  pool_delete(builder->pool);
  vector_delete(builder->vec);
  UTILITY_FREE(builder);
}
void builder_build(Builder *builder, Sexp *ast) {
  builder_expression(builder, ast);
  value_set_reg(builder->gen, builder->block);
  puts("target triple = \"x86_64-pc-linux-gnu\"\n");
  puts("define i32 @main() {");
  value_pretty(builder->block);
  puts("}");
}
Value *builder_expression(Builder *builder, Sexp *ast) {
  switch (sexp_get_tag(ast)) {
  case AST_IDENTIFIER:
    return builder_identifier(builder, ast);
  case AST_INTEGER_CONSTANT:
    return builder_integer_constant(builder, ast);
  case AST_ADDITIVE_EXPRESSION:
    return builder_additive_expression(builder, ast);
  case AST_ASSIGNMENT_EXPRESSION:
    return builder_assignment_expression(builder, ast);
  case AST_DECLARATION:
    return builder_declaration(builder, ast);
  case AST_STATEMENT:
    return builder_statement(builder, ast);
  case AST_COMPOUND_STATEMENT:
    return builder_compound_statement(builder, ast);
  case AST_DECLARATION_LIST:
    return builder_ast_map(builder, ast, builder_declaration);
  case AST_STATEMENT_LIST:
    return builder_ast_map(builder, ast, builder_statement);
  case AST_EXPRESSION_STATEMENT:
    return builder_expression_statement(builder, ast);
  case AST_JUMP_STATEMENT:
    return builder_jump_statement(builder, ast);
  case AST_TRANSLATION_UNIT:
    return builder_ast_map(builder, ast, builder_expression);
  case AST_EXTERNAL_DECLARATION:
    return NULL;
  case AST_FUNCTION_DEFINITION:
    return builder_function_definition(builder, ast);
  default:
    assert(0);
    return NULL;
  }
}
Value *builder_alloc_value(Builder *builder, ValueKind kind) {
  return pool_alloc(builder->pool, kind);
}
