#include "builder.h"

#include "ast/tag.h"
#include "builder/declaration.h"
#include "builder/definition.h"
#include "builder/expression.h"
#include "builder/lexical.h"
#include "builder/table.h"
#include "ir/block.h"
#include "ir/function.h"
#include "ir/global.h"
#include "ir/instruction.h"
#include "ir/module.h"
#include "ir/type.h"
#include "ir/value.h"
#include "sexp/sexp.h"
#include "statement.h"
#include "utility/utility.h"

struct struct_Builder {
  Module *module;
  Table *table;
  Function *func;
  Value *retval, *value;
  Type *type;
  TypeSpec *spec;
  Block *next[BUILDER_NEXT_COUNT];
};

static void builder_finish_next(Builder *builder) {
  BuilderNextTag tag = 0;
  builder->func = NULL;
  builder->retval = builder->value = NULL;
  builder->type = NULL;
  while (tag < BUILDER_NEXT_COUNT) {
    builder_set_next(builder, tag++, NULL);
  }
}
static Bool builder_function_is_void(Builder *builder) {
  Type *type = function_return_type(builder->func);
  return type_is_void(type);
}

const char *identifier_symbol(Sexp *ast) {
  UTILITY_ASSERT(AST_IDENTIFIER == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  UTILITY_ASSERT(sexp_is_symbol(ast));
  return sexp_get_symbol(ast);
}

Builder *builder_new(Module *module) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->module = module;
  builder->table = table_new();
  builder->spec = type_spec_new();
  builder_finish_next(builder);
  return builder;
}
void builder_delete(Builder *builder) {
  type_spec_delete(builder->spec);
  table_delete(builder->table);
  UTILITY_FREE(builder);
}
void builder_init_next(Builder *builder, Function *func) {
  Block *alloc = builder_new_block(builder);
  Block *entry = builder_new_block(builder);
  builder->func = func;
  builder_set_next(builder, BUILDER_NEXT_ALLOC, alloc);
  builder_set_next(builder, BUILDER_NEXT_CURRENT, entry);
  builder_set_next(builder, BUILDER_NEXT_ENTRY, entry);
  function_insert(builder->func, alloc);
}
void builder_init_return(Builder *builder) {
  Block *ret = builder_new_block(builder);
  builder_set_next(builder, BUILDER_NEXT_RETURN, ret);
  if (!builder_function_is_void(builder)) {
    builder_new_local(builder);
    builder->retval = builder_get_value(builder);
  }
}
void builder_finish_return(Builder *builder) {
  Block *ret = builder_get_next(builder, BUILDER_NEXT_RETURN);
  Value *retval = builder_get_retval(builder);
  builder_instruction_br(builder, ret);
  builder_jump_block(builder, ret);
  if (!builder_function_is_void(builder)) {
    builder_instruction_load(builder, retval);
    retval = builder_get_value(builder);
  }
  builder_instruction_ret(builder, retval);
}
void builder_function_finish(Builder *builder) {
  Block *alloc = builder_get_next(builder, BUILDER_NEXT_ALLOC);
  Block *entry = builder_get_next(builder, BUILDER_NEXT_ENTRY);
  builder_instruction_ret(builder, NULL);
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
void builder_init_global(Builder *builder, Value *dst, Value *src) {
  Global *global = value_as_global(dst);
  Constant *init = value_as_constant(src);
  global_set_init(global, init);
  module_insert_prior(builder->module, global);
}
Block *builder_label(Builder *builder, const char *label) {
  Block *block = table_label_find(builder->table, label);
  if (!block) {
    block = builder_new_block(builder);
    table_label_insert(builder->table, label, block);
  }
  return block;
}
void builder_insert_global(Builder *builder, const char *symbol,
                           Global *global) {
  table_insert_global(builder->table, symbol, global);
}
void builder_insert_local(Builder *builder, const char *symbol,
                          Instruction *instr) {
  table_insert_local(builder->table, symbol, instr);
}
void builder_find_identifier(Builder *builder, const char *symbol) {
  Value *value = table_find(builder->table, symbol, builder->module);
  builder_set_value(builder, value);
}
void builder_jump_block(Builder *builder, Block *dest) {
  builder_set_next(builder, BUILDER_NEXT_CURRENT, dest);
  function_insert(builder->func, dest);
}
Bool builder_is_local(Builder *builder) {
  return builder->func != NULL;
}
void builder_cast(Builder *builder, Value *val, Type *dst) {
  Type *src = value_type(val);
  if (!type_equals(src, dst)) {
    int lhs = type_sizeof(src), rhs = type_sizeof(dst);
    UTILITY_ASSERT(lhs != rhs);
    if (lhs < rhs) {
      builder_instruction_sext(builder, val);
    } else if (rhs < lhs) {
      builder_instruction_trunc(builder, val);
    }
  }
}
Module *builder_get_module(Builder *builder) {
  return builder->module;
}
Value *builder_get_retval(Builder *builder) {
  builder->value = builder->retval;
  return builder->retval;
}
Value *builder_get_value(Builder *builder) {
  return builder->value;
}
void builder_set_value(Builder *builder, Value *value) {
  builder->value = value;
}
Type *builder_get_type(Builder *builder) {
  return builder->type;
}
void builder_set_type(Builder *builder) {
  Module *module = builder_get_module(builder);
  builder->type = type_new_from_spec(module, builder->spec);
}
void builder_set_type_int(Builder *builder) {
  Module *module = builder_get_module(builder);
  builder->type = module_type_int(module);
}
void builder_set_type_value(Builder *builder) {
  builder->type = value_type(builder->value);
}
void builder_set_type_spec(Builder *builder, TypeSpecIndex i) {
  type_spec_set(builder->spec, i);
}
void builder_reset_type_spec(Builder *builder) {
  type_spec_reset(builder->spec);
}
Block *builder_get_next(Builder *builder, BuilderNextTag tag) {
  UTILITY_ASSERT(0 <= tag && tag < BUILDER_NEXT_COUNT);
  return builder->next[tag];
}
Block *builder_set_next(Builder *builder, BuilderNextTag tag, Block *next) {
  UTILITY_ASSERT(0 <= tag && tag < BUILDER_NEXT_COUNT);
  UTILITY_SWAP(Block *, builder->next[tag], next);
  return next;
}
void builder_ast_map(Builder *builder, Sexp *ast) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    builder_ast(builder, sexp_car(ast));
  }
}
void builder_ast(Builder *builder, Sexp *ast) {
  if (sexp_is_nil(ast)) {
    return;
  }
  switch (sexp_get_tag(ast)) {
  case AST_IDENTIFIER:
    builder_identifier(builder, ast);
    break;
  case AST_TYPEDEF_IDENTIFIER:
    builder_typedef_identifier(builder, ast);
    break;
  case AST_FLOATING_CONSTANT:
    builder_floating_constant(builder, ast);
    break;
  case AST_INTEGER_CONSTANT:
    builder_integer_constant(builder, ast);
    break;
  case AST_ENUMERATION_CONSTANT:
    builder_enumeration_constant(builder, ast);
    break;
  case AST_CHARACTER_CONSTANT:
    builder_character_constant(builder, ast);
    break;
  case AST_STRING_LITERAL:
    builder_string_literal(builder, ast);
    break;
  case AST_PRIMARY_EXPRESSION:
    builder_primary_expression(builder, ast);
    break;
  case AST_POSTFIX_EXPRESSION:
    builder_postfix_expression(builder, ast);
    break;
  case AST_ARGUMENT_EXPRESSION_LIST:
    builder_argument_expression_list(builder, ast);
    break;
  case AST_UNARY_EXPRESSION:
    builder_unary_expression(builder, ast);
    break;
  case AST_CAST_EXPRESSION:
    builder_cast_expression(builder, ast);
    break;
  case AST_MULTIPLICATIVE_EXPRESSION:
    builder_multiplicative_expression(builder, ast);
    break;
  case AST_ADDITIVE_EXPRESSION:
    builder_additive_expression(builder, ast);
    break;
  case AST_SHIFT_EXPRESSION:
    builder_shift_expression(builder, ast);
    break;
  case AST_RELATIONAL_EXPRESSION:
    builder_relational_expression(builder, ast);
    break;
  case AST_EQUALITY_EXPRESSION:
    builder_equality_expression(builder, ast);
    break;
  case AST_AND_EXPRESSION:
    builder_and_expression(builder, ast);
    break;
  case AST_EXCLUSIVE_OR_EXPRESSION:
    builder_exclusive_or_expression(builder, ast);
    break;
  case AST_INCLUSIVE_OR_EXPRESSION:
    builder_inclusive_or_expression(builder, ast);
    break;
  case AST_LOGICAL_AND_EXPRESSION:
    builder_logical_and_expression(builder, ast);
    break;
  case AST_LOGICAL_OR_EXPRESSION:
    builder_logical_or_expression(builder, ast);
    break;
  case AST_CONDITIONAL_EXPRESSION:
    builder_conditional_expression(builder, ast);
    break;
  case AST_ASSIGNMENT_EXPRESSION:
    builder_assignment_expression(builder, ast);
    break;
  case AST_EXPRESSION:
    builder_expression(builder, ast);
    break;
  case AST_CONSTANT_EXPRESSION:
    builder_constant_expression(builder, ast);
    break;
  case AST_DECLARATION:
    builder_declaration(builder, ast);
    break;
  case AST_DECLARATION_SPECIFIERS:
    builder_declaration_specifiers(builder, ast);
    break;
  case AST_INIT_DECLARATOR_LIST:
    builder_init_declarator_list(builder, ast);
    break;
  case AST_INIT_DECLARATOR:
    builder_init_declarator(builder, ast);
    break;
  case AST_STORAGE_CLASS_SPECIFIER:
    builder_storage_class_specifier(builder, ast);
    break;
  case AST_TYPE_SPECIFIER:
    builder_type_specifier(builder, ast);
    break;
  case AST_STRUCT_OR_UNION_SPECIFIER:
    builder_struct_or_union_specifier(builder, ast);
    break;
  case AST_STRUCT_DECLARATION_LIST:
    builder_struct_declaration_list(builder, ast);
    break;
  case AST_STRUCT_DECLARATION:
    builder_struct_declaration(builder, ast);
    break;
  case AST_SPECIFIER_QUALIFIER_LIST:
    builder_specifier_qualifier_list(builder, ast);
    break;
  case AST_STRUCT_DECLARATOR_LIST:
    builder_struct_declarator_list(builder, ast);
    break;
  case AST_STRUCT_DECLARATOR:
    builder_struct_declarator(builder, ast);
    break;
  case AST_ENUM_SPECIFIER:
    builder_enum_specifier(builder, ast);
    break;
  case AST_ENUMERATOR_LIST:
    builder_enumerator_list(builder, ast);
    break;
  case AST_ENUMERATOR:
    builder_enumerator(builder, ast);
    break;
  case AST_TYPE_QUALIFIER:
    builder_type_qualifier(builder, ast);
    break;
  case AST_DECLARATOR:
    builder_declarator(builder, ast);
    break;
  case AST_DIRECT_DECLARATOR:
    builder_direct_declarator(builder, ast);
    break;
  case AST_POINTER:
    builder_pointer(builder, ast);
    break;
  case AST_TYPE_QUALIFIER_LIST:
    builder_type_qualifier_list(builder, ast);
    break;
  case AST_PARAMETER_LIST:
    builder_parameter_list(builder, ast);
    break;
  case AST_PARAMETER_DECLARATION:
    builder_parameter_declaration(builder, ast);
    break;
  case AST_IDENTIFIER_LIST:
    builder_identifier_list(builder, ast);
    break;
  case AST_TYPE_NAME:
    builder_type_name(builder, ast);
    break;
  case AST_ABSTRACT_DECLARATOR:
    builder_abstract_declarator(builder, ast);
    break;
  case AST_DIRECT_ABSTRACT_DECLARATOR:
    builder_direct_abstract_declarator(builder, ast);
    break;
  case AST_TYPEDEF_NAME:
    builder_typedef_name(builder, ast);
    break;
  case AST_INITIALIZER:
    builder_initializer(builder, ast);
    break;
  case AST_INITIALIZER_LIST:
    builder_initializer_list(builder, ast);
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
    builder_declaration_list(builder, ast);
    break;
  case AST_STATEMENT_LIST:
    builder_statement_list(builder, ast);
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
    builder_translation_unit(builder, ast);
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
