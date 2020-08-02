#include "module.h"

#include "declaration.h"
#include "utility.h"
#include "vector.h"

struct struct_Module {
  Vector *decls;
};

Module *module_new(void) {
  Module *module = UTILITY_MALLOC(Module);
  module->decls = vector_new((Destructor)declaration_delete);
  return module;
}
void module_delete(Module *module) {
  assert(module);
  vector_delete(module->decls);
  UTILITY_FREE(module);
}
void module_insert(Module *module, Declaration *decl) {
  assert(module);
  vector_push(module->decls, decl);
}
void module_print(FILE *fp, Module *module) {
  ElemType *it;
  assert(module);
  for (it = vector_begin(module->decls); it != vector_end(module->decls);
       ++it) {
    declaration_print(fp, (Declaration *)*it);
  }
}
