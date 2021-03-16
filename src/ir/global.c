#include "global.h"

#include <stdio.h>

#include "builder/builder.h"
#include "ir/constant.h"
#include "ir/module.h"
#include "ir/type.h"
#include "ir/value.h"
#include "utility/utility.h"

struct struct_Global {
  ValueKind kind;
  Type *type;
  const char *name;
  Constant *init;
  Bool prior;
};

Global *global_new(void) {
  Global *global = UTILITY_MALLOC(Global);
  global->kind = VALUE_GLOBAL;
  global->type = NULL;
  global->name = NULL;
  global->init = NULL;
  global->prior = false;
  return global;
}
void global_delete(Global *global) {
  UTILITY_FREE(global);
}
Type *global_type(Global *global) {
  return global->type;
}
void global_set_init(Global *global, Constant *init) {
  global->init = init;
}
Bool global_is_prior(Global *global) {
  return global->prior;
}
void global_set_prior(Global *global) {
  global->prior = true;
}
void global_print(Global *global) {
  UTILITY_ASSERT(global->name);
  printf("@%s", global->name);
}
void global_print_type(Global *global) {
  type_print(global->type);
  printf("*");
}
void global_pretty(Global *global) {
  global_print(global);
  printf(" = global ");
  type_print(global->type);
  printf(" ");
  if (global->init) {
    constant_print(global->init);
  } else {
    printf("0");
  }
  printf(", align 4\n");
}

void builder_new_global(Builder *builder, const char *symbol) {
  Module *module = builder_get_module(builder);
  Global *global = module_new_global(module);
  global->type = builder_get_type(builder);
  global->name = symbol;
  builder_insert_global(builder, symbol, global);
  builder_set_value(builder, global_as_value(global));
}
