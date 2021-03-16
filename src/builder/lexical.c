#include "lexical.h"

#include "ast/tag.h"
#include "builder/builder.h"
#include "ir/constant.h"
#include "ir/instruction.h"
#include "ir/type.h"
#include "ir/value.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

void builder_identifier(Builder *builder, Sexp *ast) {
  const char *symbol;
  Value *value;
  UTILITY_ASSERT(AST_IDENTIFIER == sexp_get_tag(ast));
  symbol = identifier_symbol(ast);
  builder_find_identifier(builder, symbol);
  value = builder_get_value(builder);
  builder_instruction_load(builder, value);
  value = builder_get_value(builder);
  builder_cast(builder, value, builder_get_type(builder));
}
void builder_typedef_identifier(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_TYPEDEF_IDENTIFIER == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_floating_constant(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_FLOATING_CONSTANT == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_integer_constant(Builder *builder, Sexp *ast) {
  const char *symbol;
  UTILITY_ASSERT(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  UTILITY_ASSERT(sexp_is_symbol(ast));
  symbol = sexp_get_symbol(ast);
  builder_new_integer(builder, symbol);
}
void builder_enumeration_constant(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_ENUMERATION_CONSTANT == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_character_constant(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_CHARACTER_CONSTANT == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
void builder_string_literal(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_STRING_LITERAL == sexp_get_tag(ast));
  UTILITY_UNUSED(builder);
  UTILITY_ASSERT(0);
}
