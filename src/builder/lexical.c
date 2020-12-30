#include "lexical.h"

#include "ast/tag.h"
#include "builder.h"
#include "constant.h"
#include "instruction.h"
#include "sexp.h"
#include "utility.h"

void builder_identifier(Builder *builder, Sexp *ast) {
  const char *symbol;
  Value *value;
  UTILITY_ASSERT(AST_IDENTIFIER == sexp_get_tag(ast));
  symbol = identifier_symbol(ast);
  builder_find_identifier(builder, symbol);
  value = builder_get_value(builder);
  builder_instruction_load(builder, value);
}
void builder_integer_constant(Builder *builder, Sexp *ast) {
  const char *symbol;
  UTILITY_ASSERT(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  UTILITY_ASSERT(sexp_is_symbol(ast));
  symbol = sexp_get_symbol(ast);
  builder_new_integer(builder, symbol);
}
