#include "builder.h"
#include "module.h"
#include "print.h"
#include "result.h"

int main(void) {
  Result *result = result_new();
  int ret = result_parse(result);
  if (0 == ret) {
    Sexp *ast = result_get_sexp(result);
    Builder *builder = builder_new();
    Module *module = builder_new_module(builder);
    print_ast(ast);
    module_build(module, ast);
    module_print(stdout, module);
    builder_delete(builder);
  }
  result_delete(result);
  return ret;
}
