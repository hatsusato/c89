#include "ir/module.h"

#include <stdio.h>

#include "ir/function.h"
#include "ir/pool.h"
#include "utility.h"
#include "vector.h"

struct struct_Module {
  Pool *pool;
  Vector *vec;
};

Module *module_new(void) {
  Module *module = UTILITY_MALLOC(Module);
  module->pool = pool_new();
  module->vec = vector_new(NULL);
  return module;
}
void module_delete(Module *module) {
  vector_delete(module->vec);
  pool_delete(module->pool);
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
void *module_get(Module *module) {
  return module->pool;
}
