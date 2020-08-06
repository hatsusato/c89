#include "builder.h"
#include "module.h"
#include "print.h"
#include "result.h"

int main(void) {
  Result *result = result_new();
  int ret = result_parse(result);
  if (0 == ret) {
    Sexp *ast = result_get_sexp(result);
    Module *module = module_new();
    Builder *builder = builder_new(module);
    print_ast(ast);
    module_build(builder, ast);
    module_print(stdout, module);
    builder_delete(builder);
    module_delete(module);
  }
  result_delete(result);
  return ret;
}
