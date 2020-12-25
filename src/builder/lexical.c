#include "lexical.h"

#include "ast/tag.h"
#include "builder.h"
#include "constant.h"
#include "instruction.h"
#include "sexp.h"
#include "utility.h"
#include "value.h"

Value *builder_identifier(Builder *builder, Sexp *ast) {
  Value *expr = builder_find_identifier(builder, ast);
  Instruction *instr = builder_instruction_load(builder, expr);
  return instruction_as_value(instr);
}
Value *builder_integer_constant(Builder *builder, Sexp *ast) {
  const char *symbol = integer_symbol(ast);
  Constant *integer = builder_new_integer(builder, symbol);
  return constant_as_value(integer);
}
