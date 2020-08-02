#include "generate.h"
#include "module.h"
#include "print.h"
#include "result.h"

int main(void) {
  Result *result = result_new();
  int ret = result_parse(result);
  if (0 == ret) {
    Sexp *ast = result_get_sexp(result);
    Module *module = module_build(ast);
    print_ast(ast);
    generate_translation_unit(ast);
    module_print(stdout, module);
    module_delete(module);
  }
  result_delete(result);
  return ret;
}
