#include "lexical.h"

#include "ast/tag.h"
#include "builder.h"
#include "constant.h"
#include "instruction.h"
#include "sexp.h"
#include "utility.h"
#include "value.h"

void builder_identifier(Builder *builder, Sexp *ast) {
  Value *expr = builder_find_identifier(builder, ast);
  builder_instruction_load(builder, expr);
}
void builder_integer_constant(Builder *builder, Sexp *ast) {
  const char *symbol = integer_symbol(ast);
  builder_new_integer(builder, symbol);
}
