#include "module.h"

#include "function.h"
#include "utility.h"
#include "vector.h"

struct struct_Module {
  Vector *decls;
};

Module *module_new(void) {
  Module *module = UTILITY_MALLOC(Module);
  module->decls = vector_new(NULL);
  return module;
}
void module_delete(Module *module) {
  assert(module);
  vector_delete(module->decls);
  UTILITY_FREE(module);
}
void module_print(FILE *fp, Module *module) {
  ElemType *it;
  assert(module);
  for (it = vector_begin(module->decls); it != vector_end(module->decls);
       ++it) {
    function_print(fp, (Function *)*it);
  }
}
