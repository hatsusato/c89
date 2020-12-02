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
