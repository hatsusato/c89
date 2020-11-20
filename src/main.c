#include "print.h"
#include "result.h"

int main(void) {
  Result *result = result_new();
  int ret = result_parse(result);
  if (0 == ret) {
    Sexp *ast = result_get_sexp(result);
    print_ast(ast);
  }
  result_delete(result);
  return ret;
}
