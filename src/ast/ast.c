#include "ast.h"

#include "ast/tag.h"
#include "printer/printer.h"
#include "set/set.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

struct struct_Ast {
  Set *pool;
  Sexp *sexp;
};

static const char *symbol_new(const void *text, Size size) {
  char *symbol = UTILITY_MALLOC_ARRAY(char, size + 1);
  UTILITY_MEMCPY(char, symbol, text, size);
  symbol[size] = '\0';
  return symbol;
}
static void symbol_free(Generic symbol) {
  UTILITY_FREE(symbol);
}

Ast *ast_new(void) {
  Ast *ast = UTILITY_MALLOC(Ast);
  ast->pool = set_new(symbol_free, NULL);
  ast->sexp = sexp_nil();
  return ast;
}
void ast_delete(Ast *ast) {
  sexp_delete(ast->sexp);
  set_delete(ast->pool);
  UTILITY_FREE(ast);
}
Sexp *ast_get(Ast *ast) {
  return ast->sexp;
}
void ast_set(Ast *ast, Sexp *sexp) {
  assert(sexp_is_nil(ast->sexp));
  ast->sexp = sexp;
}
const char *ast_symbol(Ast *ast, const char *text, Size leng) {
  ConstGeneric found;
  assert('\0' == text[leng]);
  found = set_find(ast->pool, text);
  if (found) {
    return found;
  } else {
    const char *elem = symbol_new(text, leng);
    set_insert(ast->pool, elem);
    return elem;
  }
}
static void ast_print_sexp(Sexp *sexp, Printer *printer) {
  if (sexp_is_pair(sexp)) {
    printer_print(printer, "(");
    printer_indent(printer, 1);
    ast_print_sexp(sexp_car(sexp), printer);
    for (sexp = sexp_cdr(sexp); sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
      printer_newline(printer);
      ast_print_sexp(sexp_car(sexp), printer);
    }
    printer_indent(printer, -1);
    printer_print(printer, ")");
  } else if (sexp_is_symbol(sexp)) {
    printer_print(printer, "\"%s\"", sexp_get_symbol(sexp));
  } else if (sexp_is_number(sexp)) {
    printer_print(printer, "'%s'", ast_show(sexp_get_number(sexp)));
  } else {
    printer_print(printer, "()");
  }
}
void ast_print(Ast *ast, Printer *printer) {
  ast_print_sexp(ast->sexp, printer);
  printer_newline(printer);
}
