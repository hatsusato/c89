#include "ir/module.h"

#include <stdio.h>

#include "ir/function.h"
#include "ir/value_kind.h"
#include "utility.h"
#include "vector.h"

struct struct_Module {
  ValueKind kind;
  Vector *vec;
};

Module *module_new(void) {
  Module *module = UTILITY_MALLOC(Module);
  module->kind = VALUE_MODULE;
  module->vec = vector_new(NULL);
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
    function_pretty(*begin++);
  }
}
