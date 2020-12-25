#include "expression.h"

#include "ast/tag.h"
#include "builder.h"
#include "instruction.h"
#include "sexp.h"
#include "utility.h"
#include "value.h"

Value *builder_additive_expression(Builder *builder, Sexp *ast) {
  Value *lhs = builder_ast(builder, sexp_at(ast, 1));
  Value *rhs = builder_ast(builder, sexp_at(ast, 3));
  Instruction *instr = NULL;
  UTILITY_ASSERT(AST_ADDITIVE_EXPRESSION == sexp_get_tag(ast));
  switch (sexp_get_tag(sexp_at(ast, 2))) {
  case AST_PLUS:
    instr = builder_instruction_add(builder, lhs, rhs);
    break;
  case AST_MINUS:
    instr = builder_instruction_sub(builder, lhs, rhs);
    break;
  default:
    UTILITY_ASSERT(0);
    break;
  }
  return instruction_as_value(instr);
}
Value *builder_assignment_expression(Builder *builder, Sexp *ast) {
  Value *lhs = builder_find_identifier(builder, sexp_at(ast, 1));
  Value *rhs = builder_ast(builder, sexp_at(ast, 3));
  Instruction *instr = builder_instruction_store(builder, rhs, lhs);
  UTILITY_ASSERT(AST_ASSIGNMENT_EXPRESSION == sexp_get_tag(ast));
  UTILITY_ASSERT(AST_ASSIGN == sexp_get_tag(sexp_at(ast, 2)));
  return instruction_as_value(instr);
}
Value *builder_constant_expression(Builder *builder, Sexp *ast) {
  UTILITY_ASSERT(AST_CONSTANT_EXPRESSION == sexp_get_tag(ast));
  return builder_ast(builder, sexp_at(ast, 1));
}
