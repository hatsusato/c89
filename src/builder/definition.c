#include "definition.h"

#include "ast/tag.h"
#include "builder.h"
#include "instruction.h"
#include "sexp.h"
#include "utility.h"
#include "value.h"

static void builder_function_return(Builder *builder) {
  Instruction *retval = builder_get_retval(builder);
  Instruction *instr =
      builder_instruction_load(builder, instruction_as_value(retval));
  builder_instruction_ret(builder, instruction_as_value(instr));
}

Value *builder_external_declaration(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_EXTERNAL_DECLARATION == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  UTILITY_ASSERT(AST_DECLARATION == sexp_get_tag(ast));
  ast = sexp_at(ast, 2);
  UTILITY_ASSERT(AST_INIT_DECLARATOR_LIST == sexp_get_tag(ast));
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
  }
  return NULL;
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
