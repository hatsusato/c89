#include "ast/ast.h"
#include "ir/module.h"
#include "print.h"
#include "scanner/scanner.h"

static void build(Sexp *ast) {
  Module *module = module_new();
  module_build(module, ast);
  module_pretty(module);
  module_delete(module);
}

int main(void) {
  yyscan_t scanner = scanner_new();
  int ret = scanner_parse(scanner);
  if (0 == ret) {
    Sexp *ast = ast_get(scanner_get(scanner));
    print_ast(ast);
    build(ast);
  }
  scanner_delete(scanner);
  return ret;
}
