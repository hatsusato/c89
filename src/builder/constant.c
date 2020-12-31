#include "constant.h"

#include <stdio.h>

#include "builder.h"
#include "module.h"
#include "utility.h"
#include "value.h"

struct struct_Constant {
  ValueKind kind;
  Type *type;
  const char *symbol;
};

Constant *constant_new(void) {
  Constant *constant = UTILITY_MALLOC(Constant);
  constant->kind = VALUE_CONSTANT;
  constant->type = NULL;
  constant->symbol = NULL;
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
  Constant *constant = module_new_constant(module);
  constant->type = module_new_type_integer(module, 32);
  constant->symbol = integer;
  builder_set_value(builder, constant_as_value(constant));
}
