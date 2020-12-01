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
  Vector *stack;
  Value *func, *block;
};

static void builder_integer_constant(Builder *builder, Sexp *ast) {
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  builder_stack_push(builder, VALUE_INTEGER_CONSTANT);
  builder_stack_init(builder, ast);
}
static void builder_identifier(Builder *builder, Sexp *ast) {
  assert(AST_IDENTIFIER == sexp_get_tag(ast));
  builder_stack_push(builder, VALUE_INSTRUCTION_LOAD);
  builder_stack_push_identifier(builder, ast);
  builder_stack_insert(builder);
  builder_stack_drop(builder);
}
static void builder_function_definition(Builder *builder, Sexp *ast) {
  assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  assert(5 == sexp_length(ast));
  builder->func = pool_alloc(builder->pool, VALUE_FUNCTION);
  builder_stack_push(builder, VALUE_BLOCK);
  builder_stack_pop_block(builder);
  builder_ast(builder, sexp_at(ast, 4));
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
  builder->stack = vector_new(NULL);
  builder->func = builder->block = NULL;
  return builder;
}
void builder_delete(Builder *builder) {
  vector_delete(builder->stack);
  table_delete(builder->table);
  pool_delete(builder->pool);
  UTILITY_FREE(builder);
}
void builder_build(Builder *builder, Sexp *ast) {
  builder_ast(builder, ast);
  assert(vector_empty(builder->stack));
}
void builder_print(Builder *builder) {
  RegisterGenerator *gen = register_generator_new();
  value_set_reg(gen, builder->func);
  register_generator_delete(gen);
  puts("target triple = \"x86_64-pc-linux-gnu\"\n");
  value_pretty(builder->func);
}

static Value *builder_stack_top(Builder *builder) {
  assert(!vector_empty(builder->stack));
  return vector_back(builder->stack);
}
Bool builder_stack_empty(Builder *builder) {
  return vector_empty(builder->stack);
}
void builder_stack_push(Builder *builder, ValueKind kind) {
  Value *value = pool_alloc(builder->pool, kind);
  if (VALUE_BLOCK == kind) {
    value_insert(builder->func, value);
  }
  vector_push(builder->stack, value);
}
void builder_stack_push_identifier(Builder *builder, Sexp *ast) {
  Value *value;
  assert(AST_IDENTIFIER == sexp_get_tag(ast));
  value = table_find(builder->table, ast);
  vector_push(builder->stack, value);
}
void builder_stack_init(Builder *builder, Sexp *ast) {
  Value *value = builder_stack_top(builder);
  switch (builder_stack_top_kind(builder)) {
  case VALUE_INTEGER_CONSTANT:
    assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
    ast = sexp_at(ast, 1);
    assert(sexp_is_symbol(ast));
    value_set_value(value, sexp_get_symbol(ast));
    break;
  case VALUE_INSTRUCTION_ALLOCA:
    table_insert(builder->table, ast, value);
    break;
  default:
    break;
  }
}
void builder_stack_register(Builder *builder) {
  Value *value = builder_stack_top(builder);
  if (value_is_instruction(value)) {
    value_insert(builder->block, value);
  }
}
Value *builder_stack_drop(Builder *builder) {
  Value *value = builder_stack_top(builder);
  vector_pop(builder->stack);
  return value;
}
void builder_stack_insert(Builder *builder) {
  Value *src = builder_stack_drop(builder);
  Value *dst = builder_stack_top(builder);
  value_insert(dst, src);
  vector_push(builder->stack, src);
}
ValueKind builder_stack_top_kind(Builder *builder) {
  return value_kind(builder_stack_top(builder));
}
void builder_stack_swap(Builder *builder) {
  Value *first = builder_stack_drop(builder);
  Value *second = builder_stack_drop(builder);
  vector_push(builder->stack, first);
  vector_push(builder->stack, second);
}
void builder_stack_pop_block(Builder *builder) {
  assert(VALUE_BLOCK == builder_stack_top_kind(builder));
  builder->block = builder_stack_drop(builder);
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
