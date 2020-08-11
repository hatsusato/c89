#include "declaration.h"

#include "ast.h"
#include "builder.h"
#include "function.h"
#include "module.h"
#include "sexp.h"
#include "utility.h"

struct struct_Declaration {
  DeclarationTag tag;
  void *data;
};

static Declaration *declaration_new(DeclarationTag tag, void *data) {
  Declaration *decl = UTILITY_MALLOC(Declaration);
  decl->tag = tag;
  decl->data = data;
  return decl;
}

Declaration *declaration_new_function(Function *func) {
  return declaration_new(DECLARATION_FUNCTION, func);
}
void declaration_delete(Declaration *decl) {
  assert(decl);
  function_delete(decl->data);
  UTILITY_FREE(decl);
}
Function *declaration_function(Declaration *decl) {
  assert(decl);
  return DECLARATION_FUNCTION == decl->tag ? decl->data : NULL;
}
void declaration_build(Builder *builder, Sexp *ast) {
  assert(sexp_is_pair(ast) && sexp_is_number(sexp_car(ast)));
  switch (ast_get(ast)) {
  case AST_FUNCTION_DEFINITION:
    function_build(builder, ast);
    return;
  default:
    return;
  }
}
void declaration_print(FILE *fp, Declaration *decl) {
  assert(decl);
  switch (decl->tag) {
  case DECLARATION_FUNCTION:
    function_print(fp, decl->data);
    return;
  }
}
