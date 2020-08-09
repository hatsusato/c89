#include "builder.h"

#include "function.h"
#include "module.h"
#include "utility.h"

struct struct_Builder {
  Module *module;
  Function *func;
};

Builder *builder_new(void) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->module = NULL;
  builder->func = NULL;
  return builder;
}
void builder_new_module(Builder *builder) {
  assert(builder);
  assert(!builder->module);
  builder->module = module_new();
}
void builder_new_function(Builder *builder) {
  assert(builder);
  assert(!builder->func);
  builder->func = function_new();
}
void builder_delete(Builder *builder) {
  assert(builder);
  assert(!builder->func);
  module_delete(builder->module);
  UTILITY_FREE(builder);
}
Module *builder_module(Builder *builder) {
  assert(builder);
  return builder->module;
}
Function *builder_function(Builder *builder) {
  assert(builder);
  return builder->func;
}
