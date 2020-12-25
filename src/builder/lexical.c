#include "lexical.h"

#include "ast/tag.h"
#include "builder.h"
#include "constant.h"
#include "instruction.h"
#include "sexp.h"
#include "utility.h"
#include "value.h"

const char *builder_identifier_symbol(Sexp *ast) {
  UTILITY_ASSERT(AST_IDENTIFIER == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  UTILITY_ASSERT(sexp_is_symbol(ast));
  return sexp_get_symbol(ast);
}
Value *builder_identifier(Builder *builder, Sexp *ast) {
  Instruction *expr = builder_find_alloca(builder, ast);
  Instruction *instr =
      builder_instruction_load(builder, instruction_as_value(expr));
  return instruction_as_value(instr);
}
Value *builder_integer_constant(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  UTILITY_ASSERT(sexp_is_symbol(ast));
  return constant_as_value(builder_new_integer(builder, sexp_get_symbol(ast)));
}
