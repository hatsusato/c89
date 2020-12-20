#include "ir/stack.h"

#include "compare.h"
#include "ir/block.h"
#include "ir/constant.h"
#include "ir/function.h"
#include "ir/instruction.h"
#include "ir/module.h"
#include "ir/pool.h"
#include "ir/stack_impl.h"
#include "ir/table.h"
#include "map.h"
#include "vector.h"

struct struct_Stack {
  Pool *pool;
  Module *module;
  Table *table;
  Map *labels;
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
static int count_return(Sexp *ast) {
  if (sexp_is_pair(ast)) {
    return count_return(sexp_car(ast)) + count_return(sexp_cdr(ast));
  } else {
    return sexp_is_number(ast) && AST_RETURN == sexp_get_number(ast);
  }
}

Stack *stack_new(Module *module) {
  Stack *stack = UTILITY_MALLOC(Stack);
  int i;
  stack->pool = module_get(module);
  stack->module = module;
  stack->table = table_new();
  stack->labels = stack_new_labels();
  stack->func = NULL;
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
Module *stack_get_module(Stack *stack) {
  return stack->module;
}
void stack_build(Stack *stack, Sexp *ast) {
  Function *func = module_new_function(stack->module);
  Block *alloc = stack_new_block(stack);
  Block *entry = stack_new_block(stack);
  Block *ret = 1 < count_return(ast) ? stack_new_block(stack) : NULL;
  stack->func = func;
  function_init(func, ast);
  function_insert(func, alloc);
  stack_set_next(stack, STACK_NEXT_ALLOC, alloc);
  stack_set_next(stack, STACK_NEXT_CURRENT, entry);
  stack_set_next(stack, STACK_NEXT_RETURN, ret);
  stack_ast(stack, ast);
  block_append(alloc, entry);
  function_finish(func);
}

Value *stack_new_integer(Stack *stack, const char *integer) {
  Constant *value = constant_integer(integer);
  pool_insert_constant(stack->pool, value);
  return constant_as_value(value);
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
void stack_alloca(Stack *stack, const char *symbol, Instruction *instr) {
  table_insert(stack->table, symbol, instruction_as_value(instr));
}
Value *stack_find_alloca(Stack *stack, const char *symbol) {
  return table_find(stack->table, symbol);
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
