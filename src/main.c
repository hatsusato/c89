#include <stdio.h>

#include "ast/ast.h"
#include "ast/convert/convert.h"
#include "builder/builder.h"
#include "ir/module.h"
#include "printer/printer.h"
#include "scanner/parse.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

static void build(Module *module, Ast *ast) {
  Builder *builder = builder_new(module);
  builder_ast(builder, ast_get(ast));
  builder_delete(builder);
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
    Printer *printer = printer_new(stdout);
    Sexp *sexp = ast_get(ast);
    ast_set(ast, ast_convert(sexp));
    sexp_delete(sexp);
    if (is_debug(argc, argv)) {
      ast_print(ast, printer);
    } else {
      Module *module = module_new();
      build(module, ast);
      module_pretty(module, printer);
      module_delete(module);
    }
    printer_delete(printer);
  }
  ast_delete(ast);
  return ret;
}
