#include "ir/instruction.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "builder.h"
#include "ir/value.h"
#include "sexp.h"
#include "utility.h"

Value *instruction_build(Builder *builder, Sexp *ast) {
  Value *instr;
  switch (sexp_get_tag(ast)) {
  case AST_ADDITIVE_EXPRESSION:
    assert(sexp_is_number(sexp_at(ast, 2)));
    assert(AST_PLUS == sexp_get_number(sexp_at(ast, 2)));
    instr = builder_alloc_value(builder, VALUE_INSTRUCTION);
    value_insert(instr, builder_expression(builder, sexp_at(ast, 1)));
    value_insert(instr, builder_expression(builder, sexp_at(ast, 3)));
    break;
  case AST_JUMP_STATEMENT:
    ast = sexp_at(ast, 2);
    instr = builder_alloc_value(builder, VALUE_INSTRUCTION_RET);
    if (!sexp_is_nil(ast)) {
      value_insert(instr, builder_expression(builder, ast));
    }
    break;
  default:
    assert(0);
    break;
  }
  return instr;
}
