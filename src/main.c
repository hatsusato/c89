#include "module.h"
#include "print.h"
#include "result.h"

int main(void) {
  Result *result = result_new();
  int ret = result_parse(result);
  if (0 == ret) {
    Sexp *ast = result_get_sexp(result);
    Module *module = module_new();
    print_ast(ast);
    module_build(module, ast);
    module_print(stdout, module);
    module_delete(module);
  }
  result_delete(result);
  return ret;
}
