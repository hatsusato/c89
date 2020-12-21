#include "ir/declaration.h"

#include "ast/ast_tag.h"
#include "ir/builder.h"
#include "ir/instruction.h"
#include "ir/lexical.h"
#include "ir/value.h"
#include "sexp.h"
#include "utility.h"

Value *builder_declaration(Builder *builder, Sexp *ast) {
  assert(AST_DECLARATION == sexp_get_tag(ast));
  return builder_ast(builder, sexp_at(ast, 2));
}
Value *builder_init_declarator(Builder *builder, Sexp *ast) {
  Value *src, *dst;
  Instruction *instr;
  assert(AST_INIT_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    return builder_declarator(builder, sexp_at(ast, 1));
  case 4:
    src = builder_ast(builder, sexp_at(ast, 3));
    dst = builder_declarator(builder, sexp_at(ast, 1));
    instr = builder_instruction_store(builder, src, dst);
    return instruction_as_value(instr);
  default:
    assert(0);
    return NULL;
  }
}
Value *builder_declarator(Builder *builder, Sexp *ast) {
  assert(AST_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    return builder_direct_declarator(builder, sexp_at(ast, 1));
  case 3:
    return builder_direct_declarator(builder, sexp_at(ast, 2));
  default:
    assert(0);
    return NULL;
  }
}
Value *builder_direct_declarator(Builder *builder, Sexp *ast) {
  const char *symbol;
  Instruction *instr;
  assert(AST_DIRECT_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    symbol = builder_identifier_symbol(sexp_at(ast, 1));
    instr = builder_instruction_alloca(builder, symbol);
    return instruction_as_value(instr);
  case 4:
    return builder_declarator(builder, sexp_at(ast, 2));
  case 5:
    /* FALLTHROUGH */
  default:
    assert(0);
    return NULL;
  }
}
