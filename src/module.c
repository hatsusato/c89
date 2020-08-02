#include "module.h"

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
