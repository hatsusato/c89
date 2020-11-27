#include "builder.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "sexp.h"
#include "utility.h"

struct struct_Builder {
  int reg, last;
};

static AstTag get_tag(Sexp *ast) {
  assert(sexp_is_pair(ast));
  ast = sexp_car(ast);
  assert(sexp_is_number(ast));
  return sexp_get_number(ast);
}
static void builder_expression(Builder *, Sexp *);
static void builder_integer_constant(Builder *builder, Sexp *ast) {
  assert(AST_INTEGER_CONSTANT == get_tag(ast));
  ast = sexp_at(ast, 1);
  assert(sexp_is_symbol(ast));
  builder->last = builder->reg++;
  printf("  %%%d = add i32 0, %s\n", builder->last, sexp_get_symbol(ast));
}
static void builder_additive_expression(Builder *builder, Sexp *ast) {
  int lhs, rhs;
  assert(AST_ADDITIVE_EXPRESSION == get_tag(ast));
  assert(sexp_is_number(sexp_at(ast, 2)));
  assert(AST_PLUS == sexp_get_number(sexp_at(ast, 2)));
  builder_expression(builder, sexp_at(ast, 1));
  lhs = builder->last;
  builder_expression(builder, sexp_at(ast, 3));
  rhs = builder->last;
  builder->last = builder->reg++;
  printf("  %%%d = add i32 %%%d, %%%d\n", builder->last, lhs, rhs);
}
static void builder_expression(Builder *builder, Sexp *ast) {
  switch (get_tag(ast)) {
  case AST_INTEGER_CONSTANT:
    builder_integer_constant(builder, ast);
    break;
  case AST_ADDITIVE_EXPRESSION:
    builder_additive_expression(builder, ast);
    break;
  default:
    assert(0);
    break;
  }
}
static void builder_jump_statement(Builder *builder, Sexp *ast) {
  assert(AST_JUMP_STATEMENT == get_tag(ast));
  ast = sexp_at(ast, 2);
  if (sexp_is_nil(ast)) {
    puts("  ret void");
  } else {
    builder_expression(builder, ast);
    printf("  ret i32 %%%d\n", builder->last);
  }
}

Builder *builder_new(void) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->reg = builder->last = 0;
  return builder;
}
void builder_delete(Builder *builder) {
  UTILITY_FREE(builder);
}
