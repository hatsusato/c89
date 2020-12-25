#include "global.h"

#include "utility.h"
#include "value.h"

struct struct_Global {
  ValueKind kind;
};

Global *global_new(void) {
  Global *global = UTILITY_MALLOC(Global);
  global->kind = VALUE_GLOBAL;
  return global;
}
void global_delete(Global *global) {
  UTILITY_FREE(global);
}
