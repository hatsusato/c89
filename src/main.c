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
  int ret = scanner_parse(ast);
  if (0 == ret) {
    Sexp *sexp = ast_get(ast);
    print_ast(sexp);
    build(sexp);
  }
  ast_delete(ast);
  return ret;
}
