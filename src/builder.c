#include "builder.h"

#include "module.h"
#include "utility.h"

struct struct_Builder {
  Module *module;
};

Builder *builder_new(Module *module) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->module = module;
  return builder;
}
void builder_delete(Builder *builder) {
  assert(builder);
  UTILITY_FREE(builder);
}
Module *builder_module(Builder *builder) {
  assert(builder);
  return builder->module;
}
