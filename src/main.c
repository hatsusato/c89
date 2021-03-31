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
  Ast *ast = ast_new();
  Scanner *scanner = scanner_new(ast);
  int ret = scanner_parse(scanner);
  if (0 == ret) {
    Sexp *ast = ast_get(scanner_get(scanner));
    print_ast(ast);
    build(ast);
  }
  scanner_delete(scanner);
  ast_delete(ast);
  return ret;
}
