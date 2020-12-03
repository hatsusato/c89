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
  stack->func = function_new(pool);
  return stack;
}
void stack_delete(Stack *stack) {
  function_delete(stack->func);
  vector_delete(stack->stack);
  table_delete(stack->table);
  UTILITY_FREE(stack);
}
Value *stack_build(Stack *stack, Sexp *ast) {
  stack_ast(stack, ast);
  assert(vector_empty(stack->stack));
  return function_finish(stack->func);
}

static void stack_push_symbol(Stack *stack, const char *symbol) {
  Value *value = table_find(stack->table, symbol);
  assert(VALUE_INSTRUCTION_ALLOCA == value_kind(value));
  stack_push(stack, value);
}

Value *stack_new_value(Stack *stack, ValueKind kind) {
  return stack_push(stack, pool_alloc(stack->pool, kind));
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
void stack_register(Stack *stack) {
  Value *value = stack_top(stack);
  assert(value_is_instruction(value));
  function_insert_to_current(stack->func, value);
}
Value *stack_push(Stack *stack, Value *value) {
  vector_push(stack->stack, value);
  return value;
}
void stack_add(Stack *stack, Value *value) {
  value_insert(stack_top(stack), value);
}
Value *stack_pop(Stack *stack) {
  Value *value = stack_top(stack);
  vector_pop(stack->stack);
  return value;
}
Value *stack_top(Stack *stack) {
  assert(!vector_empty(stack->stack));
  return vector_back(stack->stack);
}
ValueKind stack_top_kind(Stack *stack) {
  return value_kind(stack_top(stack));
}
Value *stack_get_next_block(Stack *stack) {
  return function_get_next(stack->func);
}
void stack_change_flow(Stack *stack, Value *current, Value *next) {
  assert(!next || VALUE_BLOCK == value_kind(next));
  function_set_current(stack->func, current);
  function_set_next(stack->func, next);
}
void stack_return(Stack *stack) {
  if (function_get_return(stack->func)) {
    stack_store_to_symbol(stack, "$retval");
    stack_pop(stack);
    stack_push(stack, function_get_return(stack->func));
    stack_instruction_br(stack);
  } else {
    stack_instruction_ret(stack);
  }
  function_set_next(stack->func, NULL);
}
void stack_swap(Stack *stack) {
  Value *first = stack_pop(stack);
  Value *second = stack_pop(stack);
  stack_push(stack, first);
  stack_push(stack, second);
}

void stack_ret_init(Stack *stack) {
  function_set_return(stack->func, stack_new_block(stack));
}
Value *stack_ret(Stack *stack) {
  return function_get_return(stack->func);
}
void stack_insert_allocs(Stack *stack) {
  function_insert_allocs(stack->func);
}
void stack_set_function_name(Stack *stack, Sexp *ast) {
  switch (sexp_get_tag(ast)) {
  case AST_IDENTIFIER:
    assert(2 == sexp_length(ast));
    ast = sexp_at(ast, 1);
    assert(sexp_is_symbol(ast));
    value_set_value(function_get_func(stack->func), sexp_get_symbol(ast));
    break;
  case AST_DECLARATOR:
    switch (sexp_length(ast)) {
    case 2:
      stack_set_function_name(stack, sexp_at(ast, 1));
      break;
    case 3:
      stack_set_function_name(stack, sexp_at(ast, 2));
      break;
    default:
      assert(0);
      break;
    }
    break;
  case AST_DIRECT_DECLARATOR:
    switch (sexp_length(ast)) {
    case 2:
      stack_set_function_name(stack, sexp_at(ast, 1));
      break;
    case 4:
      stack_set_function_name(stack, sexp_at(ast, 2));
      break;
    default:
      stack_set_function_name(stack, sexp_at(ast, 1));
      break;
    }
    break;
  case AST_FUNCTION_DEFINITION:
    stack_set_function_name(stack, sexp_at(ast, 2));
    break;
  default:
    assert(0);
    break;
  }
}
