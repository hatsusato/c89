#include "builder.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "ir/builder_impl.h"
#include "ir/declaration.h"
#include "ir/expression.h"
#include "ir/instruction.h"
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
  Value *func, *block, *allocs, *next, *ret;
  Sexp *body;
};

static void builder_integer_constant(Builder *builder, Sexp *ast) {
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  builder_stack_new_value(builder, VALUE_INTEGER_CONSTANT);
  builder_stack_set_symbol(builder, sexp_get_symbol(ast));
}
static void builder_identifier(Builder *builder, Sexp *ast) {
  assert(AST_IDENTIFIER == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  builder_stack_push_symbol(builder, sexp_get_symbol(ast));
  builder_instruction_load(builder);
}
static void builder_function_definition(Builder *builder, Sexp *ast) {
  Value *block = builder_stack_new_block(builder);
  assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  assert(5 == sexp_length(ast));
  builder->func = pool_alloc(builder->pool, VALUE_FUNCTION);
  builder->allocs = builder_stack_new_block(builder);
  builder->body = sexp_at(ast, 4);
  builder_stack_set_current_block(builder, block);
  if (builder_multiple_return(builder)) {
    Value *next = builder_stack_new_block(builder);
    builder->ret = next;
    builder_stack_set_next_block(builder, next);
    builder_instruction_alloca(builder, "$retval");
    builder_stack_pop(builder);
    builder_ast(builder, builder->body);
    builder_stack_set_current_block(builder, next);
    builder_stack_push_symbol(builder, "$retval");
    builder_instruction_load(builder);
    builder_instruction_ret(builder);
  } else {
    builder_ast(builder, builder->body);
  }
  value_prepend(value_at(builder->func, 0), builder->allocs);
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
  builder->func = builder->block = builder->allocs = builder->next =
      builder->ret = NULL;
  builder->body = sexp_nil();
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

static int count_return(Sexp *ast) {
  if (sexp_is_pair(ast)) {
    return count_return(sexp_car(ast)) + count_return(sexp_cdr(ast));
  } else {
    return sexp_is_number(ast) && AST_RETURN == sexp_get_number(ast);
  }
}
Bool builder_multiple_return(Builder *builder) {
  return 1 < count_return(builder->body);
}
Bool builder_stack_empty(Builder *builder) {
  return vector_empty(builder->stack);
}
Value *builder_stack_new_value(Builder *builder, ValueKind kind) {
  return builder_stack_push(builder, pool_alloc(builder->pool, kind));
}
Value *builder_stack_new_block(Builder *builder) {
  return pool_alloc(builder->pool, VALUE_BLOCK);
}
void builder_stack_push_symbol(Builder *builder, const char *symbol) {
  Value *value = table_find(builder->table, symbol);
  builder_stack_push(builder, value);
  assert(VALUE_INSTRUCTION_ALLOCA == builder_stack_top_kind(builder));
}
void builder_stack_insert_symbol(Builder *builder, const char *symbol) {
  assert(VALUE_INSTRUCTION_ALLOCA == builder_stack_top_kind(builder));
  table_insert(builder->table, symbol, builder_stack_top(builder));
}
void builder_stack_set_symbol(Builder *builder, const char *symbol) {
  value_set_value(builder_stack_top(builder), symbol);
}
void builder_stack_register(Builder *builder) {
  Value *value = builder_stack_top(builder);
  assert(value_is_instruction(value));
  if (VALUE_INSTRUCTION_ALLOCA == builder_stack_top_kind(builder)) {
    value_insert(builder->allocs, value);
  } else {
    value_insert(builder->block, value);
  }
  if (value_is_terminator(value)) {
    builder_stack_pop(builder);
  }
}
Value *builder_stack_push(Builder *builder, Value *value) {
  vector_push(builder->stack, value);
  return value;
}
void builder_stack_add(Builder *builder, Value *value) {
  value_insert(builder_stack_top(builder), value);
}
Value *builder_stack_pop(Builder *builder) {
  Value *value = builder_stack_top(builder);
  vector_pop(builder->stack);
  return value;
}
Value *builder_stack_top(Builder *builder) {
  assert(!vector_empty(builder->stack));
  return vector_back(builder->stack);
}
ValueKind builder_stack_top_kind(Builder *builder) {
  return value_kind(builder_stack_top(builder));
}
void builder_stack_set_next_block(Builder *builder, Value *block) {
  assert(!block || VALUE_BLOCK == value_kind(block));
  builder->next = block;
}
Value *builder_stack_get_next_block(Builder *builder) {
  return builder->next;
}
void builder_stack_return(Builder *builder) {
  if (builder->ret) {
    builder_stack_push_symbol(builder, "$retval");
    builder_instruction_store(builder);
    builder_stack_pop(builder);
    builder_stack_push(builder, builder->ret);
    builder_instruction_br(builder);
  } else {
    builder_instruction_ret(builder);
  }
  builder->next = NULL;
}
void builder_stack_set_current_block(Builder *builder, Value *block) {
  assert(VALUE_BLOCK == value_kind(block));
  builder->block = block;
  value_insert(builder->func, block);
}
void builder_stack_swap(Builder *builder) {
  Value *first = builder_stack_pop(builder);
  Value *second = builder_stack_pop(builder);
  builder_stack_push(builder, first);
  builder_stack_push(builder, second);
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
