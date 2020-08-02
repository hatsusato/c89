#include "declaration.h"

#include "ast.h"
#include "function.h"
#include "sexp.h"
#include "utility.h"

struct struct_Declaration {
  DeclarationTag tag;
  void *data;
};

static Declaration *declaration_new(DeclarationTag tag) {
  Declaration *decl = UTILITY_MALLOC(Declaration);
  decl->tag = tag;
  decl->data = NULL;
  return decl;
}
static Declaration *declaration_new_function(Sexp *ast) {
  Declaration *decl = declaration_new(DECLARATION_FUNCTION);
  decl->data = function_build(ast);
  return decl;
}

Declaration *declaration_build(Sexp *ast) {
  assert(sexp_is_pair(ast) && sexp_is_number(sexp_car(ast)));
  switch (ast_get(ast)) {
  case AST_FUNCTION_DEFINITION:
    return declaration_new_function(ast);
  default:
    return NULL;
  }
}
void declaration_delete(Declaration *decl) {
  if (decl) {
    function_delete(decl->data);
    UTILITY_FREE(decl);
  }
}
void declaration_print(FILE *fp, Declaration *decl) {
  if (decl) {
    switch (decl->tag) {
    case DECLARATION_FUNCTION:
      function_print(fp, decl->data);
      return;
    }
  }
}
