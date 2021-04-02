#include "ast/ast.h"
#include "builder/builder.h"
#include "ir/module.h"
#include "print.h"
#include "printer/printer.h"
#include "scanner/parse.h"

static void build(Sexp *ast) {
  Printer *printer = printer_new(stdout);
  Module *module = module_new();
  Builder *builder = builder_new(module);
  builder_ast(builder, ast);
  builder_delete(builder);
  module_pretty(module, printer);
  module_delete(module);
  printer_delete(printer);
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
