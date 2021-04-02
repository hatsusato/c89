#include <stdio.h>

#include "ast/ast.h"
#include "builder/builder.h"
#include "ir/module.h"
#include "printer/printer.h"
#include "scanner/parse.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

static void build(Module *module, Sexp *ast) {
  Builder *builder = builder_new(module);
  builder_ast(builder, ast);
  builder_delete(builder);
}
static void print(Sexp *ast, Printer *printer) {
  sexp_print(ast, printer);
  printer_newline(printer);
}
static Bool is_debug(int argc, char *argv[]) {
  int i;
  for (i = 1; i < argc; ++i) {
    if (utility_strcmp(argv[i], "--debug") == 0) {
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  Ast *ast = ast_new();
  int ret = scanner_parse(ast);
  if (0 == ret) {
    Sexp *sexp = ast_get(ast);
    Module *module = module_new();
    Printer *printer = printer_new(stdout);
    if (is_debug(argc, argv)) {
      print(sexp, printer);
    } else {
      build(module, sexp);
      module_pretty(module, printer);
    }
    printer_delete(printer);
    module_delete(module);
  }
  ast_delete(ast);
  return ret;
}
