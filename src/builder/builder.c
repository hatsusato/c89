#include "builder.h"

#include "ast/tag.h"
#include "block.h"
#include "declaration.h"
#include "definition.h"
#include "expression.h"
#include "function.h"
#include "global.h"
#include "instruction.h"
#include "lexical.h"
#include "module.h"
#include "sexp.h"
#include "statement.h"
#include "table.h"
#include "utility.h"
#include "value.h"

struct struct_Builder {
  Module *module;
  Table *table;
  Function *func;
  Instruction *retval;
  Value *value;
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
    builder->retval = builder_new_instruction(builder, INSTRUCTION_ALLOCA);
  }
  return ret;
}
static void builder_finish_next(Builder *builder) {
  BuilderNextTag tag = 0;
  builder->func = NULL;
  builder->retval = NULL;
  builder->value = NULL;
  while (tag < BUILDER_NEXT_COUNT) {
    builder_set_next(builder, tag++, NULL);
  }
}

const char *identifier_symbol(Sexp *ast) {
  UTILITY_ASSERT(AST_IDENTIFIER == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  UTILITY_ASSERT(sexp_is_symbol(ast));
  return sexp_get_symbol(ast);
}
const char *integer_symbol(Sexp *ast) {
  UTILITY_ASSERT(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  UTILITY_ASSERT(sexp_is_symbol(ast));
  return sexp_get_symbol(ast);
}

Builder *builder_new(Module *module) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->module = module;
  builder->table = table_new(module);
  builder_finish_next(builder);
  return builder;
}
void builder_delete(Builder *builder) {
  table_delete(builder->table);
  UTILITY_FREE(builder);
}
Block *builder_function_init(Builder *builder, Sexp *ast) {
  Function *func = builder_new_function(builder, ast);
  builder->func = func;
  return builder_init_next(builder, ast);
}
void builder_function_finish(Builder *builder) {
  Block *alloc = builder_get_next(builder, BUILDER_NEXT_ALLOC);
  Block *entry = builder_get_next(builder, BUILDER_NEXT_ENTRY);
  block_append(alloc, entry);
  function_set_id(builder->func);
  table_clear(builder->table);
  builder_finish_next(builder);
}
void builder_push_table(Builder *builder) {
  table_push(builder->table);
}
void builder_pop_table(Builder *builder) {
  table_pop(builder->table);
}
void builder_init_global(Builder *builder, Global *global, Sexp *init) {
  Value *constant;
  builder_integer_constant(builder, init);
  constant = builder_get_value(builder);
  global_set_init(global, value_as_constant(constant));
  module_insert_prior(builder->module, global);
}
Block *builder_label(Builder *builder, Sexp *ident) {
  const char *label = identifier_symbol(ident);
  Block *block = table_label_find(builder->table, label);
  if (!block) {
    block = builder_new_block(builder);
    table_label_insert(builder->table, label, block);
  }
  return block;
}
void builder_insert_global(Builder *builder, Sexp *ident, Global *global) {
  const char *symbol = identifier_symbol(ident);
  table_insert_global(builder->table, symbol, global);
}
void builder_insert_local(Builder *builder, Sexp *ident, Instruction *instr) {
  const char *symbol = identifier_symbol(ident);
  UTILITY_ASSERT(INSTRUCTION_ALLOCA == instruction_kind(instr));
  table_insert_local(builder->table, symbol, instr);
}
Value *builder_find_identifier(Builder *builder, Sexp *ident) {
  const char *symbol = identifier_symbol(ident);
  return table_find(builder->table, symbol);
}
void builder_jump_block(Builder *builder, Block *dest) {
  UTILITY_ASSERT(dest);
  builder_set_next(builder, BUILDER_NEXT_CURRENT, dest);
  function_insert(builder->func, dest);
}
Module *builder_get_module(Builder *builder) {
  return builder->module;
}
Instruction *builder_get_retval(Builder *builder) {
  return builder->retval;
}
Value *builder_get_value(Builder *builder) {
  return builder->value;
}
Value *builder_set_value(Builder *builder, Value *value) {
  UTILITY_SWAP(Value *, builder->value, value);
  return value;
}
Block *builder_get_next(Builder *builder, BuilderNextTag tag) {
  return builder->next[tag];
}
Block *builder_set_next(Builder *builder, BuilderNextTag tag, Block *next) {
  UTILITY_ASSERT(0 <= tag && tag < BUILDER_NEXT_COUNT);
  UTILITY_SWAP(Block *, builder->next[tag], next);
  return next;
}

static void builder_ast_map(Builder *builder, Sexp *ast) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    builder_ast(builder, sexp_car(ast));
  }
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
  case AST_CONSTANT_EXPRESSION:
    builder_constant_expression(builder, ast);
    break;
  case AST_DECLARATION:
    builder_declaration(builder, ast);
    break;
  case AST_INIT_DECLARATOR_LIST:
    builder_ast_map(builder, ast);
    break;
  case AST_INIT_DECLARATOR:
    builder_init_declarator(builder, ast);
    break;
  case AST_STATEMENT:
    builder_statement(builder, ast);
    break;
  case AST_LABELED_STATEMENT:
    builder_labeled_statement(builder, ast);
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
  case AST_ITERATION_STATEMENT:
    builder_iteration_statement(builder, ast);
    break;
  case AST_JUMP_STATEMENT:
    builder_jump_statement(builder, ast);
    break;
  case AST_TRANSLATION_UNIT:
    builder_ast_map(builder, ast);
    break;
  case AST_EXTERNAL_DECLARATION:
    builder_external_declaration(builder, ast);
    break;
  case AST_FUNCTION_DEFINITION:
    builder_function_definition(builder, ast);
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
}
