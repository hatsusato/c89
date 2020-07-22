#include "generate.h"

#include <stdio.h>

#include "ast.h"
#include "sexp.h"
#include "utility.h"

static const char *identifier_from_declarator(Sexp *ast);
static AstTag get_tag(Sexp *ast) {
  if (sexp_is_number(ast)) {
    return sexp_get_number(ast);
  } else if (sexp_is_pair(ast)) {
    return get_tag(sexp_car(ast));
  }
  return AST_NULL;
}
static Sexp *check_tag(Sexp *ast, AstTag tag) {
  assert(get_tag(ast) == tag);
  return sexp_cdr(ast);
}
static const char *identifier_from_identifier(Sexp *ast) {
  ast = check_tag(ast, AST_IDENTIFIER);
  ast = sexp_car(ast);
  assert(sexp_is_string(ast));
  return sexp_get_string(ast);
}
static const char *identifier_from_direct_declarator(Sexp *ast) {
  ast = check_tag(ast, AST_DIRECT_DECLARATOR);
  switch (get_tag(ast)) {
  case AST_IDENTIFIER:
    return identifier_from_identifier(sexp_at(ast, 0));
  case AST_LEFT_PAREN:
    return identifier_from_declarator(sexp_at(ast, 1));
  case AST_DIRECT_DECLARATOR:
    return identifier_from_direct_declarator(sexp_at(ast, 0));
  default:
    assert(0);
    return NULL;
  }
}
static const char *identifier_from_declarator(Sexp *ast) {
  ast = check_tag(ast, AST_DECLARATOR);
  switch (sexp_length(ast)) {
  case 1:
    return identifier_from_direct_declarator(sexp_at(ast, 0));
  case 2:
    return identifier_from_direct_declarator(sexp_at(ast, 1));
  default:
    assert(0);
    return NULL;
  }
}
