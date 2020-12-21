#include "ir/definition.h"

#include "ast/ast_tag.h"
#include "ir/block.h"
#include "ir/builder.h"
#include "ir/function.h"
#include "ir/instruction.h"
#include "ir/module.h"
#include "ir/value.h"
#include "sexp.h"
#include "utility.h"

Value *builder_function_definition(Builder *builder, Sexp *ast) {
  Block *ret;
  assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  assert(5 == sexp_length(ast));
  builder_function_init(builder, ast);
  builder_ast(builder, sexp_at(ast, 4));
  ret = builder_get_next(builder, BUILDER_NEXT_RETURN);
  if (ret) {
    Value *expr;
    Instruction *instr;
    builder_instruction_br(builder, ret);
    builder_jump_block(builder, ret);
    expr = builder_find_alloca(builder, "$retval");
    instr = builder_instruction_load(builder, expr);
    builder_instruction_ret(builder, instruction_as_value(instr));
  }
  builder_function_finish(builder);
  return NULL;
}
