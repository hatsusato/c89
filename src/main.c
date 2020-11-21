#include "lib/scanner.h"
#include "print.h"

int main(void) {
  Scanner *scanner = scanner_new();
  int ret = scanner_parse(scanner);
  if (0 == ret) {
    Sexp *ast = scanner_ast(scanner);
    print_ast(ast);
  }
  scanner_delete(scanner);
  return ret;
}
