#include "ir/stack.h"

#include "compare.h"
#include "ir/block.h"
#include "ir/constant.h"
#include "ir/function.h"
#include "ir/pool.h"
#include "ir/register.h"
#include "ir/stack_impl.h"
#include "ir/table.h"
#include "map.h"
#include "vector.h"

struct struct_Stack {
  Pool *pool;
  Table *table;
  Map *labels;
  Sexp *ast;
  Function *func;
  Block *next[STACK_NEXT_COUNT];
};

static int labels_compare(ElemType lhs, ElemType rhs, CompareExtra extra) {
  UTILITY_UNUSED(extra);
  return utility_strcmp(lhs, rhs);
}
static Map *stack_new_labels(void) {
  Compare *compare = compare_new(labels_compare);
  Map *labels = map_new(compare);
  return labels;
}
static Function *stack_new_function(Stack *stack) {
  Function *func = function_new();
  pool_insert(stack->pool, value_of(func));
  return func;
}
static int count_return(Sexp *ast) {
  if (sexp_is_pair(ast)) {
    return count_return(sexp_car(ast)) + count_return(sexp_cdr(ast));
  } else {
    return sexp_is_number(ast) && AST_RETURN == sexp_get_number(ast);
  }
}

Stack *stack_new(Pool *pool, Sexp *ast) {
  int i;
  Stack *stack = UTILITY_MALLOC(Stack);
  stack->pool = pool;
  stack->table = table_new();
  stack->labels = stack_new_labels();
  stack->ast = ast;
  stack->func = stack_new_function(stack);
  for (i = 0; i < STACK_NEXT_COUNT; ++i) {
    stack->next[i] = NULL;
  }
  return stack;
}
void stack_delete(Stack *stack) {
  map_delete(stack->labels);
  table_delete(stack->table);
  UTILITY_FREE(stack);
}
Function *stack_build(Stack *stack) {
  Block *alloc = stack_new_block(stack);
  Block *entry = stack_new_block(stack);
  Block *ret = 1 < count_return(stack->ast) ? stack_new_block(stack) : NULL;
  function_init(stack->func, stack->ast);
  function_insert(stack->func, alloc);
  stack_set_next(stack, STACK_NEXT_ALLOC, alloc);
  stack_set_next(stack, STACK_NEXT_CURRENT, entry);
  stack_set_next(stack, STACK_NEXT_RETURN, ret);
  stack_ast(stack, stack->ast);
  block_append(alloc, entry);
  function_finish(stack->func);
  return stack->func;
}

Value *stack_new_value(Stack *stack, ValueKind kind) {
  return pool_alloc(stack->pool, kind);
}
Block *stack_new_block(Stack *stack) {
  Block *block = block_new();
  pool_insert(stack->pool, value_of(block));
  return block;
}
void stack_pool_register(Stack *stack, Value *value) {
  pool_insert(stack->pool, value);
}
Value *stack_new_integer(Stack *stack, const char *integer) {
  Constant *value = constant_integer(integer);
  stack_pool_register(stack, value_of(value));
  return value_of(value);
}
Block *stack_label(Stack *stack, const char *label) {
  ElemType key = (ElemType)label;
  if (map_contains(stack->labels, key)) {
    return *map_find(stack->labels, key);
  } else {
    Block *block = stack_new_block(stack);
    map_insert(stack->labels, key, block);
    return block;
  }
}
Bool stack_last_terminator(Stack *stack) {
  Block *current = stack_get_next(stack, STACK_NEXT_CURRENT);
  assert(current);
  return block_is_terminated(current);
}
Value *stack_alloca(Stack *stack, const char *symbol) {
  Block *alloc = stack_get_next(stack, STACK_NEXT_ALLOC);
  Instruction *value =
      (Instruction *)pool_alloc(stack->pool, VALUE_INSTRUCTION_ALLOCA);
  table_insert(stack->table, symbol, value_of(value));
  block_insert(alloc, value);
  return value_of(value);
}
Value *stack_find_alloca(Stack *stack, const char *symbol) {
  Value *value = table_find(stack->table, symbol);
  assert(VALUE_INSTRUCTION_ALLOCA == value_kind(value));
  return value;
}
void stack_jump_block(Stack *stack, Block *dest) {
  assert(dest);
  stack_set_next(stack, STACK_NEXT_CURRENT, dest);
  function_insert(stack->func, dest);
}
Block *stack_get_next(Stack *stack, StackNextTag tag) {
  return stack->next[tag];
}
Block *stack_set_next(Stack *stack, StackNextTag tag, Block *next) {
  assert(0 <= tag && tag < STACK_NEXT_COUNT);
  UTILITY_SWAP(Block *, stack->next[tag], next);
  return next;
}

static Value *stack_ast_map(Stack *stack, Sexp *ast) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    stack_ast(stack, sexp_car(ast));
  }
  return NULL;
}
Value *stack_ast(Stack *stack, Sexp *ast) {
  switch (sexp_get_tag(ast)) {
  case AST_IDENTIFIER:
    return stack_identifier(stack, ast);
  case AST_INTEGER_CONSTANT:
    return stack_integer_constant(stack, ast);
  case AST_ADDITIVE_EXPRESSION:
    return stack_additive_expression(stack, ast);
  case AST_ASSIGNMENT_EXPRESSION:
    return stack_assignment_expression(stack, ast);
  case AST_CONSTANT_EXPRESSION:
    return stack_constant_expression(stack, ast);
  case AST_DECLARATION:
    return stack_declaration(stack, ast);
  case AST_INIT_DECLARATOR_LIST:
    return stack_ast_map(stack, ast);
  case AST_INIT_DECLARATOR:
    return stack_init_declarator(stack, ast);
  case AST_STATEMENT:
    return stack_statement(stack, ast);
  case AST_LABELED_STATEMENT:
    return stack_labeled_statement(stack, ast);
  case AST_COMPOUND_STATEMENT:
    return stack_compound_statement(stack, ast);
  case AST_DECLARATION_LIST:
    return stack_ast_map(stack, ast);
  case AST_STATEMENT_LIST:
    return stack_ast_map(stack, ast);
  case AST_EXPRESSION_STATEMENT:
    return stack_expression_statement(stack, ast);
  case AST_SELECTION_STATEMENT:
    return stack_selection_statement(stack, ast);
  case AST_ITERATION_STATEMENT:
    return stack_iteration_statement(stack, ast);
  case AST_JUMP_STATEMENT:
    return stack_jump_statement(stack, ast);
  case AST_TRANSLATION_UNIT:
    return stack_ast_map(stack, ast);
  case AST_EXTERNAL_DECLARATION:
    return NULL;
  case AST_FUNCTION_DEFINITION:
    return stack_function_definition(stack, ast);
  default:
    assert(0);
    return NULL;
  }
}
