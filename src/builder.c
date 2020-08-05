#include "builder.h"

#include "module.h"
#include "utility.h"

struct struct_Builder {
  Module *module;
};

Builder *builder_new(void) {
  Builder *builder = UTILITY_MALLOC(Builder);
  builder->module = module_new();
  return builder;
}
void builder_delete(Builder *builder) {
  assert(builder);
  module_delete(builder->module);
  UTILITY_FREE(builder);
}
