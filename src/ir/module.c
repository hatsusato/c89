#include "ir/module.h"

#include <stdio.h>

#include "ir/register.h"
#include "ir/value.h"
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
void module_insert(Module *module, Function *func) {
  vector_push(module->vec, func);
}
void module_pretty(Module *module) {
  ElemType *begin = vector_begin(module->vec);
  ElemType *end = vector_end(module->vec);
  puts("target triple = \"x86_64-unknown-linux-gnu\"");
  while (begin < end) {
    puts("");
    value_pretty(*begin++);
  }
}
