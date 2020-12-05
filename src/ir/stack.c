#include "ir/stack.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "ir/function.h"
#include "ir/pool.h"
#include "ir/stack_impl.h"
#include "ir/table.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"

struct struct_Stack {
  Pool *pool;
  Table *table;
  Vector *stack;
  Function *func;
};

Stack *stack_new(Pool *pool) {
  Stack *stack = UTILITY_MALLOC(Stack);
  stack->pool = pool;
  stack->table = table_new();
  stack->stack = vector_new(NULL);
  stack->func = function_new();
  return stack;
}
void stack_delete(Stack *stack) {
  function_delete(stack->func);
  vector_delete(stack->stack);
  table_delete(stack->table);
  UTILITY_FREE(stack);
}
Value *stack_build(Stack *stack, Sexp *ast) {
  function_init(stack->func, stack->pool, ast);
  stack_ast(stack, ast);
  assert(vector_empty(stack->stack));
  function_finish(stack->func);
  return function_get(stack->func, FUNCTION_FUNC);
}

static void stack_push_symbol(Stack *stack, const char *symbol) {
  Value *value = table_find(stack->table, symbol);
  assert(VALUE_INSTRUCTION_ALLOCA == value_kind(value));
  stack_push(stack, value);
}
static Value *stack_top(Stack *stack) {
  assert(!vector_empty(stack->stack));
  return vector_back(stack->stack);
}

void stack_push(Stack *stack, Value *value) {
  vector_push(stack->stack, value);
}
Value *stack_pop(Stack *stack) {
  Value *value = stack_top(stack);
  vector_pop(stack->stack);
  return value;
}
Value *stack_new_value(Stack *stack, ValueKind kind) {
  Value *value = pool_alloc(stack->pool, kind);
  stack_push(stack, value);
  return value;
}
Value *stack_new_block(Stack *stack) {
  return pool_alloc(stack->pool, VALUE_BLOCK);
}
void stack_push_integer(Stack *stack, const char *value) {
  stack_new_value(stack, VALUE_INTEGER_CONSTANT);
  value_set_value(stack_top(stack), value);
}
void stack_load_from_symbol(Stack *stack, const char *symbol) {
  stack_push_symbol(stack, symbol);
  stack_instruction_load(stack);
}
void stack_store_to_symbol(Stack *stack, const char *symbol) {
  stack_push_symbol(stack, symbol);
  stack_instruction_store(stack);
}
void stack_alloca(Stack *stack, const char *symbol) {
  Value *allocs = function_get(stack->func, FUNCTION_ALLOCS);
  Value *value = pool_alloc(stack->pool, VALUE_INSTRUCTION_ALLOCA);
  table_insert(stack->table, symbol, value);
  value_insert(allocs, value);
  stack_push(stack, value);
}
void stack_change_flow(Stack *stack, Value *current, Value *next) {
  assert(VALUE_BLOCK == value_kind(current));
  function_set(stack->func, FUNCTION_CURRENT, current);
  value_insert(function_get(stack->func, FUNCTION_FUNC), current);
  if (next) {
    assert(VALUE_BLOCK == value_kind(next));
    function_set(stack->func, FUNCTION_NEXT, next);
  }
}
Bool stack_last_terminator(Stack *stack) {
  Value *block = function_get(stack->func, FUNCTION_CURRENT);
  Value *last;
  assert(block);
  last = value_last(block);
  return last && value_is_terminator(last);
}
void stack_insert_to_block(Stack *stack) {
  Value *block = function_get(stack->func, FUNCTION_CURRENT);
  Value *value = stack_top(stack);
  assert(value_is_instruction(value));
  value_insert(block, value);
}
void stack_insert_as_operand(Stack *stack, Value *value) {
  value_insert(stack_top(stack), value);
}
Value *stack_get_next_block(Stack *stack) {
  return function_get(stack->func, FUNCTION_NEXT);
}
void stack_set_next_block(Stack *stack, Value *block) {
  function_set(stack->func, FUNCTION_NEXT, block);
}
Value *stack_get_default_block(Stack *stack) {
  Value *value = stack_top(stack);
  assert(VALUE_INSTRUCTION_SWITCH == value_kind(value));
  return value_at(value, 1);
}
Value *stack_get_return_block(Stack *stack) {
  return function_get(stack->func, FUNCTION_RET);
}
void stack_set_function_name(Stack *stack, const char *name) {
  Value *func = function_get(stack->func, FUNCTION_FUNC);
  value_set_value(func, name);
}

static void stack_ast_map(Stack *stack, Sexp *ast) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    stack_ast(stack, sexp_car(ast));
  }
}
void stack_ast(Stack *stack, Sexp *ast) {
  switch (sexp_get_tag(ast)) {
  case AST_IDENTIFIER:
    stack_identifier(stack, ast);
    break;
  case AST_INTEGER_CONSTANT:
    stack_integer_constant(stack, ast);
    break;
  case AST_ADDITIVE_EXPRESSION:
    stack_additive_expression(stack, ast);
    break;
  case AST_ASSIGNMENT_EXPRESSION:
    stack_assignment_expression(stack, ast);
    break;
  case AST_CONSTANT_EXPRESSION:
    stack_constant_expression(stack, ast);
    break;
  case AST_DECLARATION:
    stack_declaration(stack, ast);
    break;
  case AST_INIT_DECLARATOR_LIST:
    stack_ast_map(stack, ast);
    break;
  case AST_INIT_DECLARATOR:
    stack_init_declarator(stack, ast);
    break;
  case AST_STATEMENT:
    stack_statement(stack, ast);
    break;
  case AST_LABELED_STATEMENT:
    stack_labeled_statement(stack, ast);
    break;
  case AST_COMPOUND_STATEMENT:
    stack_compound_statement(stack, ast);
    break;
  case AST_DECLARATION_LIST:
    stack_ast_map(stack, ast);
    break;
  case AST_STATEMENT_LIST:
    stack_ast_map(stack, ast);
    break;
  case AST_EXPRESSION_STATEMENT:
    stack_expression_statement(stack, ast);
    break;
  case AST_SELECTION_STATEMENT:
    stack_selection_statement(stack, ast);
    break;
  case AST_JUMP_STATEMENT:
    stack_jump_statement(stack, ast);
    break;
  case AST_TRANSLATION_UNIT:
    stack_ast_map(stack, ast);
    break;
  case AST_EXTERNAL_DECLARATION:
    break;
  case AST_FUNCTION_DEFINITION:
    stack_function_definition(stack, ast);
    break;
  default:
    assert(0);
    break;
  }
}
