#include "ast.h"
#include "print.h"
#include "scanner.h"

int main(void) {
  yyscan_t scanner = scanner_new();
  int ret = scanner_parse(scanner);
  if (0 == ret) {
    Ast *ast = scanner_ast(scanner);
    print_ast(ast_get(ast));
  }
  scanner_delete(scanner);
  return ret;
}
