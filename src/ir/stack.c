#include "ir/stack.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "ir/declaration.h"
#include "ir/definition.h"
#include "ir/expression.h"
#include "ir/function.h"
#include "ir/instruction.h"
#include "ir/lexical.h"
#include "ir/pool.h"
#include "ir/register.h"
#include "ir/register_type.h"
#include "ir/stack_impl.h"
#include "ir/statement.h"
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
  RegisterGenerator *gen = register_generator_new();
  stack_ast(stack, ast);
  assert(vector_empty(stack->stack));
  value_set_reg(gen, function_get_func(stack->func));
  register_generator_delete(gen);
  return function_get_func(stack->func);
}
void stack_print(Stack *stack) {
  puts("target triple = \"x86_64-pc-linux-gnu\"\n");
  value_pretty(function_get_func(stack->func));
}

Bool stack_empty(Stack *stack) {
  return vector_empty(stack->stack);
}
Value *stack_new_value(Stack *stack, ValueKind kind) {
  return stack_push(stack, pool_alloc(stack->pool, kind));
}
Value *stack_new_block(Stack *stack) {
  return pool_alloc(stack->pool, VALUE_BLOCK);
}
void stack_push_symbol(Stack *stack, const char *symbol) {
  Value *value = table_find(stack->table, symbol);
  stack_push(stack, value);
  assert(VALUE_INSTRUCTION_ALLOCA == stack_top_kind(stack));
}
void stack_insert_symbol(Stack *stack, const char *symbol) {
  assert(VALUE_INSTRUCTION_ALLOCA == stack_top_kind(stack));
  table_insert(stack->table, symbol, stack_top(stack));
}
void stack_set_symbol(Stack *stack, const char *symbol) {
  value_set_value(stack_top(stack), symbol);
}
void stack_register(Stack *stack) {
  Value *value = stack_top(stack);
  assert(value_is_instruction(value));
  if (VALUE_INSTRUCTION_ALLOCA == stack_top_kind(stack)) {
    function_insert_to_allocs(stack->func, value);
  } else {
    function_insert_to_current(stack->func, value);
  }
  if (value_is_terminator(value)) {
    stack_pop(stack);
  }
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
void stack_set_next_block(Stack *stack, Value *block) {
  function_set_next(stack->func, block);
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
    stack_push_symbol(stack, "$retval");
    stack_instruction_store(stack);
    stack_pop(stack);
    stack_push(stack, function_get_return(stack->func));
    stack_instruction_br(stack);
  } else {
    stack_instruction_ret(stack);
  }
  function_set_next(stack->func, NULL);
}
void stack_set_current_block(Stack *stack, Value *block) {
  function_set_current(stack->func, block);
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
