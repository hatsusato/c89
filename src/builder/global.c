#include "global.h"

#include <stdio.h>

#include "builder.h"
#include "constant.h"
#include "module.h"
#include "utility.h"
#include "value.h"

struct struct_Global {
  ValueKind kind;
  const char *name;
  Constant *init;
  Bool prior;
};

Global *global_new(void) {
  Global *global = UTILITY_MALLOC(Global);
  global->kind = VALUE_GLOBAL;
  global->name = NULL;
  global->init = NULL;
  global->prior = false;
  return global;
}
void global_delete(Global *global) {
  UTILITY_FREE(global);
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
void global_pretty(Global *global) {
  global_print(global);
  printf(" = global i32 ");
  if (global->init) {
    constant_print(global->init);
  } else {
    printf("0");
  }
  printf(", align 4\n");
}

Global *builder_new_global(Builder *builder, Sexp *ident) {
  Module *module = builder_get_module(builder);
  Global *global = module_new_global(module);
  global->name = identifier_symbol(ident);
  builder_insert_global(builder, ident, global);
  return global;
}
