#include "ir/instruction.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "builder.h"
#include "ir/pool.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "sexp.h"
#include "utility.h"

struct struct_Instruction {
  ValueHeader header;
  Value *lhs, *rhs;
};
typedef struct struct_Instruction Instruction;

static void instruction_print_add(Value *instr) {
  printf("  ");
  value_print(instr);
  printf(" = add i32 ");
  value_print(value_at(instr, 0));
  printf(", ");
  value_print(value_at(instr, 1));
  printf("\n");
}
static void instruction_print_ret(Value *instr) {
  if (0 == value_length(instr)) {
    printf("  ret void");
  } else {
    printf("  ret i32 ");
    value_print(value_at(instr, 0));
  }
  printf("\n");
}

void instruction_print(Value *instr) {
  switch (value_kind(instr)) {
  case VALUE_INSTRUCTION:
    instruction_print_add(instr);
    break;
  case VALUE_INSTRUCTION_RET:
    instruction_print_ret(instr);
    break;
  default:
    assert(0);
    break;
  }
}
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
