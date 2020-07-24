#include "function.h"

#include "ast.h"
#include "sexp.h"
#include "utility.h"

struct struct_Function {
  const char *name;
};

static Sexp *check_tag(Sexp *ast, AstTag tag) {
  assert(ast_get(ast) == tag);
  return sexp_cdr(ast);
}
static void function_set_declarator(Function *, Sexp *);
static void function_set_identifier(Function *func, Sexp *ast) {
  ast = check_tag(ast, AST_IDENTIFIER);
  ast = sexp_car(ast);
  assert(sexp_is_string(ast));
  func->name = sexp_get_string(ast);
}
static void function_set_direct_declarator(Function *func, Sexp *ast) {
  ast = check_tag(ast, AST_DIRECT_DECLARATOR);
  switch (ast_get(ast)) {
  case AST_IDENTIFIER:
    function_set_identifier(func, sexp_at(ast, 0));
    break;
  case AST_LEFT_PAREN:
    function_set_declarator(func, sexp_at(ast, 1));
    break;
  case AST_DIRECT_DECLARATOR:
    function_set_direct_declarator(func, sexp_at(ast, 0));
    break;
  default:
    assert(0);
  }
}
static void function_set_declarator(Function *func, Sexp *ast) {
  ast = check_tag(ast, AST_DECLARATOR);
  switch (sexp_length(ast)) {
  case 1:
    function_set_direct_declarator(func, sexp_at(ast, 0));
    break;
  case 2:
    function_set_direct_declarator(func, sexp_at(ast, 1));
    break;
  default:
    assert(0);
  }
}

Function *function_new(void) {
  Function *func = UTILITY_MALLOC(Function);
  func->name = NULL;
  return func;
}
void function_delete(Function *func) {
  UTILITY_FREE(func);
}
void function_set(Function *func, Sexp *ast) {
  ast = check_tag(ast, AST_FUNCTION_DEFINITION);
  assert(4 == sexp_length(ast));
  function_set_declarator(func, sexp_at(ast, 1));
}
