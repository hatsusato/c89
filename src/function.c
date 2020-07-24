#include "function.h"

#include "utility.h"

struct struct_Function {
  const char *name;
};

Function *function_new(void) {
  Function *func = UTILITY_MALLOC(Function);
  func->name = NULL;
  return func;
}
void function_delete(Function *func) {
  UTILITY_FREE(func);
}
