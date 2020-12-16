#include "ir/module.h"

#include "ir/register.h"
#include "ir/value_kind.h"
#include "utility.h"
#include "vector.h"

struct struct_Module {
  ValueKind kind;
  Register reg;
  Vector *vec;
  const void *value;
};

Module *module_new(void) {
  Module *module = UTILITY_MALLOC(Module);
  module->kind = VALUE_MODULE;
  register_init(&module->reg);
  module->vec = vector_new(NULL);
  module->value = NULL;
  return module;
}
void module_delete(Module *module) {
  vector_delete(module->vec);
  UTILITY_FREE(module);
}
