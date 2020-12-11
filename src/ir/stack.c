#include "ir/stack.h"

#include "ir/function.h"
#include "ir/pool.h"
#include "ir/stack_impl.h"
#include "ir/table.h"
#include "vector.h"

struct struct_Stack {
  Pool *pool;
  Table *table;
  Vector *stack;
  Function *func;
  Value *next[STACK_NEXT_COUNT];
};

Stack *stack_new(Pool *pool) {
  int i;
  Stack *stack = UTILITY_MALLOC(Stack);
  stack->pool = pool;
  stack->table = table_new();
  stack->stack = vector_new(NULL);
  stack->func = function_new();
  for (i = 0; i < STACK_NEXT_COUNT; ++i) {
    stack->next[i] = NULL;
  }
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
  stack_set_next(stack, STACK_NEXT_CURRENT,
                 function_get(stack->func, FUNCTION_ENTRY));
  stack_set_next(stack, STACK_NEXT_RETURN,
                 function_get(stack->func, FUNCTION_RET));
  stack_ast(stack, ast);
  assert(stack_empty(stack));
  function_finish(stack->func);
  return function_get(stack->func, FUNCTION_FUNC);
}

static void stack_push_symbol(Stack *stack, const char *symbol) {
  Value *value = table_find(stack->table, symbol);
  assert(VALUE_INSTRUCTION_ALLOCA == value_kind(value));
  stack_push(stack, value);
}
static Value *stack_top(Stack *stack) {
  assert(!stack_empty(stack));
  return vector_back(stack->stack);
}

Bool stack_empty(Stack *stack) {
  return vector_empty(stack->stack);
}
void stack_push(Stack *stack, Value *value) {
  assert(value && VALUE_BLOCK != value_kind(value));
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
void stack_jump_block(Stack *stack, Value *next, Value *dest) {
  Value *func = function_get(stack->func, FUNCTION_FUNC);
  assert(next && VALUE_BLOCK == value_kind(next));
  assert(dest && VALUE_BLOCK == value_kind(dest));
  if (!stack_last_terminator(stack)) {
    stack_instruction_br(stack, next);
  }
  stack_set_next(stack, STACK_NEXT_CURRENT, dest);
  value_insert(func, dest);
}
void stack_next_block(Stack *stack, Value *next) {
  stack_jump_block(stack, next, next);
}
Bool stack_last_terminator(Stack *stack) {
  Value *block = stack_get_next(stack, STACK_NEXT_CURRENT);
  Value *last;
  assert(block);
  last = value_last(block);
  return last && value_is_terminator(last);
}
void stack_insert_to_block(Stack *stack) {
  Value *block = stack_get_next(stack, STACK_NEXT_CURRENT);
  Value *value = stack_top(stack);
  assert(value_is_instruction(value));
  value_insert(block, value);
}
void stack_insert_as_operand(Stack *stack, Value *value) {
  value_insert(stack_top(stack), value);
}
Value *stack_get_switch_instruction(Stack *stack) {
  Value *value = stack_top(stack);
  return VALUE_INSTRUCTION_SWITCH == value_kind(value) ? value : NULL;
}
Value *stack_get_next(Stack *stack, StackNextTag tag) {
  return stack->next[tag];
}
Value *stack_set_next(Stack *stack, StackNextTag tag, Value *next) {
  assert(0 <= tag && tag < STACK_NEXT_COUNT);
  UTILITY_SWAP(Value *, stack->next[tag], next);
  return next;
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
  case AST_ITERATION_STATEMENT:
    stack_iteration_statement(stack, ast);
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
