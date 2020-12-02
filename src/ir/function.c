#include "ir/function.h"

#include "ir/pool.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "utility.h"

struct struct_Function {
  Value *func, *allocs;
  Value *current, *next, *ret;
};

Function *function_new(Pool *pool) {
  Function *func = UTILITY_MALLOC(Function);
  func->func = pool_alloc(pool, VALUE_FUNCTION);
  func->allocs = pool_alloc(pool, VALUE_BLOCK);
  func->current = func->next = func->ret = NULL;
  return func;
}
void function_delete(Function *func) {
  UTILITY_FREE(func);
}
void function_insert_allocs(Function *func) {
  value_prepend(value_at(func->func, 0), func->allocs);
}
void function_insert_to_allocs(Function *func, Value *value) {
  value_insert(func->allocs, value);
}
void function_insert_to_current(Function *func, Value *value) {
  value_insert(func->current, value);
}
void function_set_current(Function *func, Value *value) {
  assert(VALUE_BLOCK == value_kind(value));
  func->current = value;
  value_insert(func->func, value);
}
Value *function_get_return(Function *func) {
  return func->ret;
}
void function_set_return(Function *func, Value *ret) {
  func->ret = ret;
}
