#include "ir.h"

#include "builder/builder.h"
#include "ir/function.h"
#include "ir/module.h"
#include "ir/value.h"

Function *builder_new_function(Builder *builder, const char *name, Type *type) {
  Module *module = builder_get_module(builder);
  Function *func = function_new(name, type);
  module_insert_value(module, value_of(func));
  return func;
}
