#include "common.h"

#include "ir/constant.h"

void builder_guard_statement(Builder *builder, Sexp *expr, Block *then_block,
                             Block *else_block) {
  Value *lhs, *rhs, *icmp;
  builder_ast(builder, expr);
  lhs = builder_get_value(builder);
  builder_new_integer(builder, "0");
  rhs = builder_get_value(builder);
  builder_instruction_icmp_ne(builder, lhs, rhs);
  icmp = builder_get_value(builder);
  builder_instruction_br_cond(builder, icmp, then_block, else_block);
}
