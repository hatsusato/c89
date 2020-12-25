#include "declaration.h"

#include "ast/tag.h"
#include "builder.h"
#include "instruction.h"
#include "sexp.h"
#include "utility.h"
#include "value.h"

static Value *builder_declarator_initializer(Builder *builder, Sexp *ast) {
  Value *src = builder_ast(builder, sexp_at(ast, 3));
  Value *dst = builder_declarator(builder, sexp_at(ast, 1));
  Instruction *instr = builder_instruction_store(builder, src, dst);
  return instruction_as_value(instr);
}
static Value *builder_direct_declarator_identifier(Builder *builder,
                                                   Sexp *ast) {
  Instruction *instr = builder_instruction_alloca(builder, sexp_at(ast, 1));
  return instruction_as_value(instr);
}

Value *builder_declaration(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_DECLARATION == sexp_get_tag(ast));
  return builder_ast(builder, sexp_at(ast, 2));
}
Value *builder_init_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_INIT_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    return builder_declarator(builder, sexp_at(ast, 1));
  case 4:
    return builder_declarator_initializer(builder, ast);
  default:
    UTILITY_ASSERT(0);
    return NULL;
  }
}
Value *builder_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    return builder_direct_declarator(builder, sexp_at(ast, 1));
  case 3:
    return builder_direct_declarator(builder, sexp_at(ast, 2));
  default:
    UTILITY_ASSERT(0);
    return NULL;
  }
}
Value *builder_direct_declarator(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_DIRECT_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    return builder_direct_declarator_identifier(builder, ast);
  case 4:
    return builder_declarator(builder, sexp_at(ast, 2));
  case 5:
    /* FALLTHROUGH */
  default:
    UTILITY_ASSERT(0);
    return NULL;
  }
}
