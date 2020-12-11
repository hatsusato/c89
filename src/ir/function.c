#include "ir/function.h"

#include "ast/ast_tag.h"
#include "ir/pool.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"

struct struct_Function {
  Value *members[FUNCTION_COUNT];
};

Function *function_new(void) {
  Function *func = UTILITY_MALLOC(Function);
  int i;
  for (i = 0; i < FUNCTION_COUNT; ++i) {
    func->members[i] = NULL;
  }
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
void function_init(Function *f, Pool *pool, Sexp *ast) {
  Value *func = pool_alloc(pool, VALUE_FUNCTION);
  Value *allocs = pool_alloc(pool, VALUE_BLOCK);
  function_set(f, FUNCTION_FUNC, func);
  function_set(f, FUNCTION_ALLOCS, allocs);
  UTILITY_UNUSED(ast);
}
