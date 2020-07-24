#include "generate.h"

#include "ast.h"
#include "function.h"
#include "sexp.h"
#include "utility.h"

static Sexp *check_tag(Sexp *ast, AstTag tag) {
  assert(ast_get(ast) == tag);
  return sexp_cdr(ast);
}
void generate_translation_unit(Sexp *ast) {
  ast = check_tag(ast, AST_TRANSLATION_UNIT);
  for (; sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    if (ast_get(ast) == AST_FUNCTION_DEFINITION) {
      Function *func = function_new();
      function_set(func, sexp_car(ast));
      function_print(func);
      function_delete(func);
    }
  }
}
