#include "ir/function.h"

#include "ir/register.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "utility.h"
#include "vector.h"

struct struct_Function {
  ValueKind kind;
  Register reg;
  Vector *vec;
  const void *value;
};

Function *function_new(void) {
  Function *func = UTILITY_MALLOC(Function);
  func->kind = VALUE_FUNCTION;
  register_init(&func->reg);
  func->vec = vector_new(NULL);
  func->value = NULL;
  return func;
}
void function_delete(Function *func) {
  vector_delete(func->vec);
  UTILITY_FREE(func);
}
void function_insert(Function *func, Value *block) {
  vector_push(func->vec, block);
}
void function_set_register(Function *func) {
  RegisterGenerator *gen = register_generator_new();
  ElemType *begin = vector_begin(func->vec);
  ElemType *end = vector_end(func->vec);
  while (begin < end) {
    value_set_reg(gen, *begin++);
  }
  register_generator_delete(gen);
}
