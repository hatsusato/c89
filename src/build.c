#include "build.h"

#include "function.h"

Function *build_function(Sexp *ast) {
  Function *func = function_new();
  const char *name = function_name(ast);
  function_set_name(func, name);
  return func;
}
