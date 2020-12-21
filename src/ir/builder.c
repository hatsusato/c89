#include "ir/builder.h"

#include "ast/ast_tag.h"
#include "compare.h"
#include "ir/block.h"
#include "ir/constant.h"
#include "ir/declaration.h"
#include "ir/definition.h"
#include "ir/expression.h"
#include "ir/function.h"
#include "ir/instruction.h"
#include "ir/lexical.h"
#include "ir/module.h"
#include "ir/statement.h"
#include "ir/table.h"
#include "ir/value.h"
#include "map.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"

struct struct_Builder {
  Module *module;
  Table *table;
  Function *func;
  Block *next[BUILDER_NEXT_COUNT];
};

static Block *builder_init_next(Builder *builder, Sexp *ast) {
  Block *alloc = builder_new_block(builder);
  Block *entry = builder_new_block(builder);
  Block *ret = NULL;
  builder_set_next(builder, BUILDER_NEXT_ALLOC, alloc);
  builder_set_next(builder, BUILDER_NEXT_CURRENT, entry);
  builder_set_next(builder, BUILDER_NEXT_ENTRY, entry);
  function_insert(builder->func, alloc);
  if (1 < function_count_return(ast)) {
    ret = builder_new_block(builder);
    builder_set_next(builder, BUILDER_NEXT_RETURN, ret);
    builder_instruction_alloca(builder, "$retval");
  }
  return ret;
}
static void builder_finish_next(Builder *builder) {
  BuilderNextTag tag = 0;
  builder->table = NULL;
  builder->func = NULL;
  while (tag < BUILDER_NEXT_COUNT) {
    builder_set_next(builder, tag++, NULL);
  }
}

Builder *builder_new(Module *module) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->module = module;
  builder_finish_next(builder);
  return builder;
}
void builder_delete(Builder *builder) {
  UTILITY_FREE(builder);
}
Block *builder_function_init(Builder *builder, Sexp *ast) {
  Function *func = builder_new_function(builder, ast);
  builder->table = table_new();
  builder->func = func;
  return builder_init_next(builder, ast);
}
void builder_function_finish(Builder *builder) {
  Block *alloc = builder_get_next(builder, BUILDER_NEXT_ALLOC);
  Block *entry = builder_get_next(builder, BUILDER_NEXT_ENTRY);
  block_append(alloc, entry);
  function_set_id(builder->func);
  table_delete(builder->table);
  builder_finish_next(builder);
}
Module *builder_get_module(Builder *builder) {
  return builder->module;
}
Block *builder_label(Builder *builder, const char *label) {
  if (table_label_contains(builder->table, label)) {
    return table_label_find(builder->table, label);
  } else {
    Block *block = builder_new_block(builder);
    table_label_insert(builder->table, label, block);
    return block;
  }
}
void builder_alloca(Builder *builder, const char *symbol, Instruction *instr) {
  table_insert(builder->table, symbol, instruction_as_value(instr));
}
Value *builder_find_alloca(Builder *builder, const char *symbol) {
  return table_find(builder->table, symbol);
}
void builder_jump_block(Builder *builder, Block *dest) {
  assert(dest);
  builder_set_next(builder, BUILDER_NEXT_CURRENT, dest);
  function_insert(builder->func, dest);
}
Block *builder_get_next(Builder *builder, BuilderNextTag tag) {
  return builder->next[tag];
}
Block *builder_set_next(Builder *builder, BuilderNextTag tag, Block *next) {
  assert(0 <= tag && tag < BUILDER_NEXT_COUNT);
  UTILITY_SWAP(Block *, builder->next[tag], next);
  return next;
}

static Value *builder_ast_map(Builder *builder, Sexp *ast) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    builder_ast(builder, sexp_car(ast));
  }
  return NULL;
}
Value *builder_ast(Builder *builder, Sexp *ast) {
  switch (sexp_get_tag(ast)) {
  case AST_IDENTIFIER:
    return builder_identifier(builder, ast);
  case AST_INTEGER_CONSTANT:
    return builder_integer_constant(builder, ast);
  case AST_ADDITIVE_EXPRESSION:
    return builder_additive_expression(builder, ast);
  case AST_ASSIGNMENT_EXPRESSION:
    return builder_assignment_expression(builder, ast);
  case AST_CONSTANT_EXPRESSION:
    return builder_constant_expression(builder, ast);
  case AST_DECLARATION:
    return builder_declaration(builder, ast);
  case AST_INIT_DECLARATOR_LIST:
    return builder_ast_map(builder, ast);
  case AST_INIT_DECLARATOR:
    return builder_init_declarator(builder, ast);
  case AST_STATEMENT:
    return builder_statement(builder, ast);
  case AST_LABELED_STATEMENT:
    return builder_labeled_statement(builder, ast);
  case AST_COMPOUND_STATEMENT:
    return builder_compound_statement(builder, ast);
  case AST_DECLARATION_LIST:
    return builder_ast_map(builder, ast);
  case AST_STATEMENT_LIST:
    return builder_ast_map(builder, ast);
  case AST_EXPRESSION_STATEMENT:
    return builder_expression_statement(builder, ast);
  case AST_SELECTION_STATEMENT:
    return builder_selection_statement(builder, ast);
  case AST_ITERATION_STATEMENT:
    return builder_iteration_statement(builder, ast);
  case AST_JUMP_STATEMENT:
    return builder_jump_statement(builder, ast);
  case AST_TRANSLATION_UNIT:
    return builder_ast_map(builder, ast);
  case AST_EXTERNAL_DECLARATION:
    return NULL;
  case AST_FUNCTION_DEFINITION:
    return builder_function_definition(builder, ast);
  default:
    assert(0);
    return NULL;
  }
}
