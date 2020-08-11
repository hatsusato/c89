#include "builder.h"

#include "function.h"
#include "module.h"
#include "utility.h"

struct struct_Builder {
  Module *module;
};

Builder *builder_new(void) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->module = NULL;
  return builder;
}
void builder_new_module(Builder *builder) {
  assert(builder);
  assert(!builder->module);
  builder->module = module_new();
}
Function *builder_new_function(Builder *builder) {
  Function *func;
  assert(builder);
  func = function_new();
  module_insert_function(builder->module, func);
  return func;
}
void builder_delete(Builder *builder) {
  assert(builder);
  module_delete(builder->module);
  UTILITY_FREE(builder);
}
Module *builder_module(Builder *builder) {
  assert(builder);
  return builder->module;
}
