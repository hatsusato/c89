#include "definition.h"

#include "ast/tag.h"
#include "builder.h"
#include "instruction.h"
#include "sexp.h"
#include "type.h"
#include "utility.h"

void builder_translation_unit(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_TRANSLATION_UNIT == sexp_get_tag(ast));
  builder_ast_map(builder, ast);
}
void builder_external_declaration(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_EXTERNAL_DECLARATION == sexp_get_tag(ast));
  UTILITY_ASSERT(!builder_is_local(builder));
  builder_ast(builder, sexp_at(ast, 1));
}
void builder_function_definition(Builder *builder, Sexp *ast) {
  Block *ret;
  int length = sexp_length(ast);
  UTILITY_ASSERT(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  if (4 == length) {
    Type *type = builder_type_integer(builder, 32);
    builder_set_type(builder, type);
  } else {
    UTILITY_ASSERT(5 == length);
    builder_ast(builder, sexp_at(ast, 1));
  }
  builder_function_init(builder, ast);
  ret = builder_get_next(builder, BUILDER_NEXT_RETURN);
  builder_ast(builder, sexp_at(ast, length - 1));
  if (ret) {
    Value *retval;
    builder_instruction_br(builder, ret);
    builder_jump_block(builder, ret);
    retval = builder_get_retval(builder);
    builder_instruction_load(builder, retval);
    retval = builder_get_value(builder);
    builder_instruction_ret(builder, retval);
  }
  builder_function_finish(builder);
}
