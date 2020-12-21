#include "ir/lexical.h"

#include "ast/ast_tag.h"
#include "ir/builder.h"
#include "ir/constant.h"
#include "ir/instruction.h"
#include "ir/value.h"
#include "sexp.h"
#include "utility.h"

const char *builder_identifier_symbol(Sexp *ast) {
  assert(AST_IDENTIFIER == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  return sexp_get_symbol(ast);
}
Value *builder_identifier(Builder *builder, Sexp *ast) {
  const char *symbol = builder_identifier_symbol(ast);
  Value *expr = builder_find_alloca(builder, symbol);
  Instruction *instr = builder_instruction_load(builder, expr);
  return instruction_as_value(instr);
}
Value *builder_integer_constant(Builder *builder, Sexp *ast) {
  assert(AST_INTEGER_CONSTANT == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  return constant_as_value(builder_new_integer(builder, sexp_get_symbol(ast)));
}
