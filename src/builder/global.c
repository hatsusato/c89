#include "global.h"

#include <stdio.h>

#include "builder.h"
#include "module.h"
#include "utility.h"
#include "value.h"

struct struct_Global {
  ValueKind kind;
  const char *name;
};

Global *global_new(void) {
  Global *global = UTILITY_MALLOC(Global);
  global->kind = VALUE_GLOBAL;
  global->name = NULL;
  return global;
}
void global_delete(Global *global) {
  UTILITY_FREE(global);
}
void global_print(Global *global) {
  UTILITY_ASSERT(global->name);
  printf("@%s", global->name);
}
void global_pretty(Global *global) {
  global_print(global);
  printf(" = global i32 0, align 4\n");
}

Global *builder_new_global(Builder *builder, const char *name) {
  Module *module = builder_get_module(builder);
  Global *global = module_new_global(module);
  global->name = name;
  return global;
}
