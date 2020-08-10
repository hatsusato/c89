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

static Declaration *declaration_new(DeclarationTag tag) {
  Declaration *decl = UTILITY_MALLOC(Declaration);
  decl->tag = tag;
  decl->data = NULL;
  return decl;
}

Declaration *declaration_new_function(Function *func) {
  Declaration *decl = declaration_new(DECLARATION_FUNCTION);
  decl->data = func;
  return decl;
}
void declaration_delete(Declaration *decl) {
  if (decl) {
    function_delete(decl->data);
    UTILITY_FREE(decl);
  }
}
Function *declaration_function(Declaration *decl) {
  assert(decl);
  return DECLARATION_FUNCTION == decl->tag ? decl->data : NULL;
}
void declaration_build(Builder *builder, Sexp *ast) {
  assert(sexp_is_pair(ast) && sexp_is_number(sexp_car(ast)));
  switch (ast_get(ast)) {
  case AST_FUNCTION_DEFINITION:
    module_insert(builder_module(builder),
                  declaration_new_function(function_build(ast)));
    return;
  default:
    return;
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
