#include "ast/ast.h"
#include "builder/builder.h"
#include "ir/module.h"
#include "print.h"
#include "scanner/scanner.h"

static void build(Sexp *ast) {
  Module *module = module_new();
  Builder *builder = builder_new(module);
  builder_ast(builder, ast);
  builder_delete(builder);
  module_pretty(module);
  module_delete(module);
}

int main(void) {
  Scanner *scanner = scanner_new();
  int ret = scanner_parse(scanner_yyscan(scanner));
  if (0 == ret) {
    Sexp *ast = ast_get(scanner_get(scanner_yyscan(scanner)));
    print_ast(ast);
    build(ast);
  }
  scanner_delete(scanner);
  return ret;
}
