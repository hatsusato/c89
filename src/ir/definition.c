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

void builder_function_build(Builder *builder, Sexp *ast) {
  Block *ret = builder_get_next(builder, BUILDER_NEXT_RETURN);
  assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  assert(5 == sexp_length(ast));
  if (ret) {
    Value *expr;
    Instruction *instr;
    builder_instruction_alloca(builder, "$retval");
    builder_ast(builder, sexp_at(ast, 4));
    builder_instruction_br(builder, ret);
    builder_jump_block(builder, ret);
    expr = builder_find_alloca(builder, "$retval");
    instr = builder_instruction_load(builder, expr);
    builder_instruction_ret(builder, instruction_as_value(instr));
  } else {
    builder_ast(builder, sexp_at(ast, 4));
  }
}
Value *builder_function_definition(Builder *builder, Sexp *ast) {
  Function *func = builder_new_function(builder, ast);
  Block *alloc = builder_get_next(builder, BUILDER_NEXT_ALLOC);
  Block *entry = builder_get_next(builder, BUILDER_NEXT_ENTRY);
  builder_function_init(builder, func);
  builder_function_build(builder, ast);
  block_append(alloc, entry);
  function_set_id(func);
  builder_function_finish(builder);
  return NULL;
}
