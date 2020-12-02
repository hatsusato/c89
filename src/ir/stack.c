#include "ir/stack.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "ir/declaration.h"
#include "ir/expression.h"
#include "ir/instruction.h"
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
  Value *func, *current, *allocs, *next, *ret;
  Sexp *body;
};

static void stack_integer_constant(Stack *stack, Sexp *ast) {
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  stack_new_value(stack, VALUE_INTEGER_CONSTANT);
  stack_set_symbol(stack, sexp_get_symbol(ast));
}
static void stack_identifier(Stack *stack, Sexp *ast) {
  assert(AST_IDENTIFIER == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  stack_push_symbol(stack, sexp_get_symbol(ast));
  stack_instruction_load(stack);
}
static void stack_function_definition(Stack *stack, Sexp *ast) {
  Value *entry = stack_new_block(stack);
  assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  assert(5 == sexp_length(ast));
  stack->func = pool_alloc(stack->pool, VALUE_FUNCTION);
  stack->allocs = stack_new_block(stack);
  stack->body = sexp_at(ast, 4);
  if (stack_multiple_return(stack)) {
    Value *next = stack_new_block(stack);
    stack->ret = next;
    stack_instruction_alloca(stack, "$retval");
    stack_pop(stack);
    stack_change_flow(stack, entry, next);
    stack_ast(stack, stack->body);
    stack_change_flow(stack, next, NULL);
    stack_push_symbol(stack, "$retval");
    stack_instruction_load(stack);
    stack_instruction_ret(stack);
  } else {
    stack_change_flow(stack, entry, NULL);
    stack_ast(stack, stack->body);
  }
  value_prepend(value_at(stack->func, 0), stack->allocs);
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
  value_set_value(stack->func, sexp_get_symbol(ast));
}
static void stack_ast_map(Stack *stack, Sexp *ast) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    stack_ast(stack, sexp_car(ast));
  }
}

Stack *stack_new(Pool *pool) {
  Stack *stack = UTILITY_MALLOC(Stack);
  stack->pool = pool;
  stack->table = table_new();
  stack->stack = vector_new(NULL);
  stack->func = stack->current = stack->allocs = stack->next = stack->ret =
      NULL;
  stack->body = sexp_nil();
  return stack;
}
void stack_delete(Stack *stack) {
  vector_delete(stack->stack);
  table_delete(stack->table);
  UTILITY_FREE(stack);
}
Value *stack_build(Stack *stack, Sexp *ast) {
  RegisterGenerator *gen = register_generator_new();
  stack_ast(stack, ast);
  assert(vector_empty(stack->stack));
  value_set_reg(gen, stack->func);
  register_generator_delete(gen);
  return stack->func;
}
void stack_print(Stack *stack) {
  puts("target triple = \"x86_64-pc-linux-gnu\"\n");
  value_pretty(stack->func);
}

static int count_return(Sexp *ast) {
  if (sexp_is_pair(ast)) {
    return count_return(sexp_car(ast)) + count_return(sexp_cdr(ast));
  } else {
    return sexp_is_number(ast) && AST_RETURN == sexp_get_number(ast);
  }
}
Bool stack_multiple_return(Stack *stack) {
  return 1 < count_return(stack->body);
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
    value_insert(stack->allocs, value);
  } else {
    value_insert(stack->current, value);
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
  assert(!block || VALUE_BLOCK == value_kind(block));
  stack->next = block;
}
Value *stack_get_next_block(Stack *stack) {
  return stack->next;
}
void stack_change_flow(Stack *stack, Value *current, Value *next) {
  assert(VALUE_BLOCK == value_kind(current));
  assert(!next || VALUE_BLOCK == value_kind(next));
  stack->current = current;
  stack->next = next;
  value_insert(stack->func, current);
}
void stack_return(Stack *stack) {
  if (stack->ret) {
    stack_push_symbol(stack, "$retval");
    stack_instruction_store(stack);
    stack_pop(stack);
    stack_push(stack, stack->ret);
    stack_instruction_br(stack);
  } else {
    stack_instruction_ret(stack);
  }
  stack->next = NULL;
}
void stack_set_current_block(Stack *stack, Value *block) {
  assert(VALUE_BLOCK == value_kind(block));
  stack->current = block;
  value_insert(stack->func, block);
}
void stack_swap(Stack *stack) {
  Value *first = stack_pop(stack);
  Value *second = stack_pop(stack);
  stack_push(stack, first);
  stack_push(stack, second);
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
  case AST_DECLARATION:
    stack_declaration(stack, ast);
    break;
  case AST_STATEMENT:
    stack_statement(stack, ast);
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
