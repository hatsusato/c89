#include "module.h"

#include "ast.h"
#include "declaration.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"

struct struct_Module {
  Vector *decls;
};

static Module *module_new(void) {
  Module *module = UTILITY_MALLOC(Module);
  module->decls = vector_new((Destructor)declaration_delete);
  return module;
}
static void module_insert(Module *module, Declaration *decl) {
  assert(module);
  vector_push(module->decls, decl);
}

Module *module_build(Sexp *ast) {
  Module *module = module_new();
  ast = sexp_next(ast, AST_TRANSLATION_UNIT);
  for (; sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    Declaration *decl = declaration_build(sexp_car(ast));
    module_insert(module, decl);
  }
  return module;
}
void module_delete(Module *module) {
  if (module) {
    vector_delete(module->decls);
    UTILITY_FREE(module);
  }
}
void module_print(FILE *fp, Module *module) {
  ElemType *it;
  assert(module);
  for (it = vector_begin(module->decls); it != vector_end(module->decls);
       ++it) {
    declaration_print(fp, (Declaration *)*it);
  }
}
