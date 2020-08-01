#include "generate.h"

#include "ast.h"
#include "build.h"
#include "function.h"
#include "sexp.h"
#include "utility.h"

void generate_translation_unit(Sexp *ast) {
  ast = sexp_next(ast, AST_TRANSLATION_UNIT);
  for (; sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    Sexp *car = sexp_car(ast);
    if (ast_get(car) == AST_FUNCTION_DEFINITION) {
      Function *func = build_function(car);
      function_print(stdout, func);
      function_delete(func);
    }
  }
}
