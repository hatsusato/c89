#include "function.h"

#include "ast.h"
#include "sexp.h"
#include "utility.h"

struct struct_Function {
  const char *name;
};

static Sexp *check_tag(Sexp *ast, AstTag tag) {
  assert(ast_get(ast) == tag);
  return sexp_cdr(ast);
}
Function *function_new(void) {
  Function *func = UTILITY_MALLOC(Function);
  func->name = NULL;
  return func;
}
void function_delete(Function *func) {
  UTILITY_FREE(func);
}
