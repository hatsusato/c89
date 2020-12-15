#include "ir/stack.h"

#include "compare.h"
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
  Vector *stack;
  Sexp *ast;
  Value *func;
  Value *prev;
  Value *next[STACK_NEXT_COUNT];
};

static int labels_compare(ElemType lhs, ElemType rhs, CompareExtra extra) {
  UTILITY_UNUSED(extra);
  return utility_strcmp(lhs, rhs);
}
static int count_return(Sexp *ast) {
  if (sexp_is_pair(ast)) {
    return count_return(sexp_car(ast)) + count_return(sexp_cdr(ast));
  } else {
    return sexp_is_number(ast) && AST_RETURN == sexp_get_number(ast);
  }
}
static Bool stack_empty(Stack *stack) {
  return vector_empty(stack->stack);
}
void stack_push(Stack *stack, Value *value) {
  assert(value && VALUE_BLOCK != value_kind(value));
  vector_push(stack->stack, value);
}

Stack *stack_new(Pool *pool, Sexp *ast) {
  int i;
  Stack *stack = UTILITY_MALLOC(Stack);
  stack->pool = pool;
  stack->table = table_new();
  stack->labels = map_new(compare_new(labels_compare));
  stack->stack = vector_new(NULL);
  stack->ast = ast;
  stack->func = pool_alloc(pool, VALUE_FUNCTION);
  stack->prev = NULL;
  for (i = 0; i < STACK_NEXT_COUNT; ++i) {
    stack->next[i] = NULL;
  }
  return stack;
}
void stack_delete(Stack *stack) {
  vector_delete(stack->stack);
  map_delete(stack->labels);
  table_delete(stack->table);
  UTILITY_FREE(stack);
}
Value *stack_build(Stack *stack) {
  RegisterGenerator *gen;
  Value *alloc = stack_new_block(stack);
  Value *entry = stack_new_block(stack);
  Value *ret = 1 < count_return(stack->ast) ? stack_new_block(stack) : NULL;
  value_insert(stack->func, alloc);
  stack_set_next(stack, STACK_NEXT_ALLOC, alloc);
  stack_set_next(stack, STACK_NEXT_CURRENT, entry);
  stack_set_next(stack, STACK_NEXT_RETURN, ret);
  stack_ast(stack, stack->ast);
  assert(stack_empty(stack));
  value_append(alloc, entry);
  value_function_clean(stack->func);
  gen = register_generator_new();
  value_set_reg(gen, stack->func);
  register_generator_delete(gen);
  return stack->func;
}

Value *stack_pop(Stack *stack) {
  Value *value = stack_top(stack);
  vector_pop(stack->stack);
  return value;
}
Value *stack_top(Stack *stack) {
  assert(!stack_empty(stack));
  return vector_back(stack->stack);
}
Value *stack_new_value(Stack *stack, ValueKind kind) {
  Value *value = pool_alloc(stack->pool, kind);
  stack_push(stack, value);
  return value;
}
Value *stack_new_block(Stack *stack) {
  return pool_alloc(stack->pool, VALUE_BLOCK);
}
Value *stack_label(Stack *stack, const char *label) {
  ElemType key = (ElemType)label;
  if (map_contains(stack->labels, key)) {
    return *map_find(stack->labels, key);
  } else {
    Value *block = stack_new_block(stack);
    map_insert(stack->labels, key, block);
    return block;
  }
}
Bool stack_last_terminator(Stack *stack) {
  Value *current = stack_get_next(stack, STACK_NEXT_CURRENT);
  Value *last = value_last(current);
  assert(current && VALUE_BLOCK == value_kind(current));
  return last && value_is_terminator(last);
}
void stack_insert_block(Stack *stack, Value *block) {
  assert(block && VALUE_BLOCK == value_kind(block));
  value_insert(stack_top(stack), block);
}
void stack_push_integer(Stack *stack, const char *value) {
  stack_new_value(stack, VALUE_INTEGER_CONSTANT);
  value_set_value(stack_top(stack), value);
}
void stack_load_from_symbol(Stack *stack, const char *symbol) {
  Value *value = stack_find_alloca(stack, symbol);
  stack_push(stack, value);
  stack_instruction_load(stack);
}
void stack_store_to_symbol(Stack *stack, const char *symbol) {
  Value *src = stack_pop(stack);
  Value *dst = stack_find_alloca(stack, symbol);
  Value *store = stack_instruction_store(stack, src, dst);
  stack_push(stack, store);
}
void stack_alloca(Stack *stack, const char *symbol) {
  Value *alloc = stack_get_next(stack, STACK_NEXT_ALLOC);
  Value *value = pool_alloc(stack->pool, VALUE_INSTRUCTION_ALLOCA);
  table_insert(stack->table, symbol, value);
  value_insert(alloc, value);
  stack_push(stack, value);
}
Value *stack_find_alloca(Stack *stack, const char *symbol) {
  Value *value = table_find(stack->table, symbol);
  assert(VALUE_INSTRUCTION_ALLOCA == value_kind(value));
  return value;
}
void stack_jump_block(Stack *stack, Value *dest) {
  assert(dest && VALUE_BLOCK == value_kind(dest));
  stack_set_next(stack, STACK_NEXT_CURRENT, dest);
  value_insert(stack->func, dest);
}
Value *stack_get_prev(Stack *stack) {
  return stack->prev;
}
Value *stack_set_prev(Stack *stack, Value *prev) {
  UTILITY_SWAP(Value *, stack->prev, prev);
  return prev;
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
  value_set_value(stack->func, name);
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
