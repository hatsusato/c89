#include "ast.h"
#include "print.h"
#include "scanner.h"

int main(void) {
  yyscan_t scanner = scanner_new();
  int ret = scanner_parse(scanner);
  if (0 == ret) {
    Sexp *ast = scanner_get(scanner);
    print_ast(ast);
  }
  scanner_delete(scanner);
  return ret;
}
