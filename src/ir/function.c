#include "ir/function.h"

#include "ast/ast_tag.h"
#include "ir/pool.h"
#include "ir/register.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"

struct struct_Function {
  Value *members[FUNCTION_COUNT];
};

static int count_return(Sexp *ast) {
  if (sexp_is_pair(ast)) {
    return count_return(sexp_car(ast)) + count_return(sexp_cdr(ast));
  } else {
    return sexp_is_number(ast) && AST_RETURN == sexp_get_number(ast);
  }
}

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
  Value *entry = pool_alloc(pool, VALUE_BLOCK);
  Value *ret = NULL;
  if (1 < count_return(ast)) {
    ret = pool_alloc(pool, VALUE_BLOCK);
  }
  function_set(f, FUNCTION_FUNC, func);
  function_set(f, FUNCTION_ALLOCS, allocs);
  function_set(f, FUNCTION_ENTRY, entry);
  function_set(f, FUNCTION_CURRENT, entry);
  function_set(f, FUNCTION_NEXT, ret);
  function_set(f, FUNCTION_RET, ret);
  value_insert(func, allocs);
}
void function_finish(Function *func) {
  RegisterGenerator *gen = register_generator_new();
  Value *f = function_get(func, FUNCTION_FUNC);
  Value *a = function_get(func, FUNCTION_ALLOCS);
  Value *e = function_get(func, FUNCTION_ENTRY);
  value_append(a, e);
  value_set_reg(gen, f);
  register_generator_delete(gen);
}
