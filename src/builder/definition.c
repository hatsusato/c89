#include "definition.h"

#include "ast/tag.h"
#include "builder.h"
#include "instruction.h"
#include "sexp.h"
#include "utility.h"
#include "value.h"

static void builder_function_return(Builder *builder) {
  Value *expr = builder_find_alloca(builder, "$retval");
  Instruction *instr = builder_instruction_load(builder, expr);
  builder_instruction_ret(builder, instruction_as_value(instr));
}

Value *builder_function_definition(Builder *builder, Sexp *ast) {
  Block *ret = builder_function_init(builder, ast);
  UTILITY_ASSERT(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  UTILITY_ASSERT(5 == sexp_length(ast));
  builder_ast(builder, sexp_at(ast, 4));
  if (ret) {
    builder_instruction_br(builder, ret);
    builder_jump_block(builder, ret);
    builder_function_return(builder);
  }
  builder_function_finish(builder);
  return NULL;
}