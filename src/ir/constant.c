#include "constant.h"

#include <stdio.h>

#include "builder/builder.h"
#include "ir/module.h"
#include "ir/type.h"
#include "ir/value.h"
#include "utility/utility.h"

struct struct_Constant {
  ValueKind kind;
  Type *type;
  const char *symbol;
};

Constant *constant_new(Module *module, const char *integer, Type *type) {
  Constant *constant = UTILITY_MALLOC(Constant);
  constant->kind = VALUE_CONSTANT;
  constant->type = type;
  constant->symbol = integer;
  module_insert_value(module, value_of(constant));
  return constant;
}
void constant_delete(Constant *constant) {
  UTILITY_FREE(constant);
}
Type *constant_type(Constant *constant) {
  return constant->type;
}
void constant_print(Constant *constant) {
  printf("%s", constant->symbol);
}

void builder_new_integer(Builder *builder, const char *integer) {
  Module *module = builder_get_module(builder);
  Type *type = builder_get_type(builder);
  Constant *constant = constant_new(module, integer, type);
  builder_set_value(builder, constant_as_value(constant));
}
