#include "ir/function.h"

#include "ir/pool.h"
#include "ir/register.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "utility.h"

struct struct_Function {
  Value *members[FUNCTION_COUNT];
};

Function *function_new(Pool *pool) {
  Function *func = UTILITY_MALLOC(Function);
  function_set(func, FUNCTION_FUNC, pool_alloc(pool, VALUE_FUNCTION));
  function_set(func, FUNCTION_ALLOCS, pool_alloc(pool, VALUE_BLOCK));
  function_set(func, FUNCTION_CURRENT, NULL);
  function_set(func, FUNCTION_NEXT, NULL);
  function_set(func, FUNCTION_RET, NULL);
  return func;
}
void function_delete(Function *func) {
  UTILITY_FREE(func);
}
Value *function_get(Function *func, FunctionMember member) {
  return func->members[member];
}
void function_set(Function *func, FunctionMember member, Value *value) {
  func->members[member] = value;
}
Value *function_finish(Function *func) {
  RegisterGenerator *gen = register_generator_new();
  Value *f = function_get(func, FUNCTION_FUNC);
  Value *a = function_get(func, FUNCTION_ALLOCS);
  Value *entry = value_at(f, 0);
  value_prepend(entry, a);
  value_set_reg(gen, f);
  register_generator_delete(gen);
  return f;
}
