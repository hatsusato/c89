#include "builder.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "ir/builder_impl.h"
#include "ir/declaration.h"
#include "ir/expression.h"
#include "ir/pool.h"
#include "ir/register.h"
#include "ir/register_type.h"
#include "ir/statement.h"
#include "ir/table.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"

struct struct_Builder {
  Pool *pool;
  Table *table;
  Vector *blocks, *stack;
  Value *func;
};

static void builder_integer_constant(Builder *builder, Sexp *ast) {
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  builder_stack_push(builder, VALUE_INTEGER_CONSTANT, sexp_at(ast, 1));
}
static void builder_identifier(Builder *builder, Sexp *ast) {
  assert(AST_IDENTIFIER == sexp_get_tag(ast));
  builder_stack_push(builder, VALUE_INSTRUCTION_LOAD, ast);
  builder_stack_insert(builder, ast);
}
static void builder_function_definition(Builder *builder, Sexp *ast) {
  assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  assert(5 == sexp_length(ast));
  builder->func = pool_alloc(builder->pool, VALUE_FUNCTION);
  vector_push(builder->blocks, pool_alloc(builder->pool, VALUE_BLOCK));
  value_insert(builder->func, vector_back(builder->blocks));
  builder_ast(builder, sexp_at(ast, 4));
  vector_pop(builder->blocks);
  ast = sexp_at(ast, 2);
  assert(AST_DECLARATOR == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(AST_DIRECT_DECLARATOR == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(AST_DIRECT_DECLARATOR == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(AST_IDENTIFIER == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  value_set_value(builder->func, sexp_get_symbol(ast));
}
static void builder_ast_map(Builder *builder, Sexp *ast) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    builder_ast(builder, sexp_car(ast));
  }
}

Builder *builder_new(void) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->pool = pool_new();
  builder->table = table_new();
  builder->blocks = vector_new(NULL);
  builder->stack = vector_new(NULL);
  builder->func = NULL;
  return builder;
}
void builder_delete(Builder *builder) {
  vector_delete(builder->stack);
  vector_delete(builder->blocks);
  table_delete(builder->table);
  pool_delete(builder->pool);
  UTILITY_FREE(builder);
}
void builder_build(Builder *builder, Sexp *ast) {
  builder_ast(builder, ast);
  assert(vector_empty(builder->blocks));
  assert(vector_empty(builder->stack));
}
void builder_print(Builder *builder) {
  RegisterGenerator *gen = register_generator_new();
  value_set_reg(gen, builder->func);
  register_generator_delete(gen);
  puts("target triple = \"x86_64-pc-linux-gnu\"\n");
  value_pretty(builder->func);
}

void builder_stack_push(Builder *builder, ValueKind kind, Sexp *ast) {
  Value *value = pool_alloc(builder->pool, kind);
  switch (kind) {
  case VALUE_INTEGER_CONSTANT:
    assert(sexp_is_symbol(ast));
    value_set_value(value, sexp_get_symbol(ast));
    break;
  case VALUE_INSTRUCTION_ALLOCA:
    table_insert(builder->table, ast, value);
    break;
  default:
    break;
  }
  vector_push(builder->stack, value);
}
Value *builder_stack_pop(Builder *builder) {
  Value *value = vector_back(builder->stack);
  vector_pop(builder->stack);
  if (value_is_instruction(value)) {
    value_insert(vector_back(builder->blocks), value);
  }
  return value;
}
void builder_stack_pop_insert(Builder *builder) {
  Value *pop = builder_stack_pop(builder);
  Value *value = vector_back(builder->stack);
  value_insert(value, pop);
}
void builder_stack_insert(Builder *builder, Sexp *ast) {
  Value *value = vector_back(builder->stack);
  value_insert(value, table_find(builder->table, ast));
}
void builder_ast(Builder *builder, Sexp *ast) {
  switch (sexp_get_tag(ast)) {
  case AST_IDENTIFIER:
    builder_identifier(builder, ast);
    break;
  case AST_INTEGER_CONSTANT:
    builder_integer_constant(builder, ast);
    break;
  case AST_ADDITIVE_EXPRESSION:
    builder_additive_expression(builder, ast);
    break;
  case AST_ASSIGNMENT_EXPRESSION:
    builder_assignment_expression(builder, ast);
    break;
  case AST_DECLARATION:
    builder_declaration(builder, ast);
    break;
  case AST_STATEMENT:
    builder_statement(builder, ast);
    break;
  case AST_COMPOUND_STATEMENT:
    builder_compound_statement(builder, ast);
    break;
  case AST_DECLARATION_LIST:
    builder_ast_map(builder, ast);
    break;
  case AST_STATEMENT_LIST:
    builder_ast_map(builder, ast);
    break;
  case AST_EXPRESSION_STATEMENT:
    builder_expression_statement(builder, ast);
    break;
  case AST_SELECTION_STATEMENT:
    builder_selection_statement(builder, ast);
    break;
  case AST_JUMP_STATEMENT:
    builder_jump_statement(builder, ast);
    break;
  case AST_TRANSLATION_UNIT:
    builder_ast_map(builder, ast);
    break;
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
