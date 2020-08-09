#include "builder.h"

#include "module.h"
#include "utility.h"

struct struct_Builder {
  Module *module;
  Function *func;
};

Builder *builder_new(Module *module) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->module = module;
  builder->func = NULL;
  return builder;
}
void builder_delete(Builder *builder) {
  assert(builder);
  assert(!builder->func);
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
