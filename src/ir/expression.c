#include "ir/expression.h"

#include "ast/ast_tag.h"
#include "ir/builder.h"
#include "ir/instruction.h"
#include "ir/lexical.h"
#include "ir/value.h"
#include "sexp.h"
#include "utility.h"

Value *builder_additive_expression(Builder *builder, Sexp *ast) {
  Value *lhs, *rhs;
  Instruction *instr = NULL;
  assert(AST_ADDITIVE_EXPRESSION == sexp_get_tag(ast));
  lhs = builder_ast(builder, sexp_at(ast, 1));
  rhs = builder_ast(builder, sexp_at(ast, 3));
  switch (sexp_get_tag(sexp_at(ast, 2))) {
  case AST_PLUS:
    instr = builder_instruction_add(builder, lhs, rhs);
    break;
  case AST_MINUS:
    instr = builder_instruction_sub(builder, lhs, rhs);
    break;
  default:
    assert(0);
    break;
  }
  return instruction_as_value(instr);
}
Value *builder_assignment_expression(Builder *builder, Sexp *ast) {
  const char *symbol;
  Value *lhs, *rhs;
  Instruction *instr;
  assert(AST_ASSIGNMENT_EXPRESSION == sexp_get_tag(ast));
  assert(AST_ASSIGN == sexp_get_tag(sexp_at(ast, 2)));
  symbol = builder_identifier_symbol(sexp_at(ast, 1));
  lhs = builder_find_alloca(builder, symbol);
  rhs = builder_ast(builder, sexp_at(ast, 3));
  instr = builder_instruction_store(builder, rhs, lhs);
  return instruction_as_value(instr);
}
Value *builder_constant_expression(Builder *builder, Sexp *ast) {
  assert(AST_CONSTANT_EXPRESSION == sexp_get_tag(ast));
  return builder_ast(builder, sexp_at(ast, 1));
}
