#include "ir/function.h"

#include "ir/pool.h"
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

void function_insert_allocs(Function *func) {
  value_prepend(value_at(function_get(func, FUNCTION_FUNC), 0),
                function_get(func, FUNCTION_ALLOCS));
}
void function_insert_to_allocs(Function *func, Value *value) {
  value_insert(function_get(func, FUNCTION_ALLOCS), value);
}
void function_insert_to_current(Function *func, Value *value) {
  value_insert(function_get(func, FUNCTION_CURRENT), value);
}
void function_set_current(Function *func, Value *value) {
  assert(VALUE_BLOCK == value_kind(value));
  function_set(func, FUNCTION_CURRENT, value);
  value_insert(function_get(func, FUNCTION_FUNC), value);
}
Value *function_get_return(Function *func) {
  return function_get(func, FUNCTION_RET);
}
void function_set_return(Function *func, Value *ret) {
  function_set(func, FUNCTION_RET, ret);
}

Value *function_get_func(Function *func) {
  return function_get(func, FUNCTION_FUNC);
}
Value *function_get_next(Function *func) {
  return function_get(func, FUNCTION_NEXT);
}
void function_set_next(Function *func, Value *value) {
  assert(!value || VALUE_BLOCK == value_kind(value));
  function_set(func, FUNCTION_NEXT, value);
}
