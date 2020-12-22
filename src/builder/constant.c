#include "constant.h"

#include <stdio.h>

#include "builder.h"
#include "module.h"
#include "utility.h"
#include "value/kind.h"

struct struct_Constant {
  ValueKind kind;
  const char *symbol;
};

Constant *constant_new(void) {
  Constant *constant = UTILITY_MALLOC(Constant);
  constant->kind = VALUE_CONSTANT;
  constant->symbol = NULL;
  return constant;
}
void constant_delete(Constant *constant) {
  UTILITY_FREE(constant);
}
void constant_print(Constant *constant) {
  printf("%s", constant->symbol);
}

Constant *builder_new_integer(Builder *builder, const char *integer) {
  Module *module = builder_get_module(builder);
  Constant *constant = module_new_constant(module);
  constant->symbol = integer;
  return constant;
}
