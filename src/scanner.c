#include "scanner.h"

#include "parser.tab.h"
#include "pool.h"
#include "sexp.h"
#include "utility.h"

struct struct_Scanner {
  yyscan_t yyscan;
  Sexp *ast;
  Pool *typedefs;
};

Scanner *scanner_new(void) {
  Scanner *scanner = UTILITY_MALLOC(Scanner);
  int ret = yylex_init(&scanner->yyscan);
  assert(0 == ret);
  (void)ret;
  yyset_extra(scanner, scanner->yyscan);
  scanner->ast = sexp_nil();
  scanner->typedefs = pool_new(NULL);
  scanner_register(scanner, "__builtin_va_list");
  return scanner;
}
void scanner_delete(Scanner *scanner) {
  pool_delete(scanner->typedefs);
  sexp_delete(scanner->ast);
  yylex_destroy(scanner->yyscan);
  UTILITY_FREE(scanner);
}
int scanner_parse(Scanner *scanner) {
  return yyparse(scanner->yyscan);
}
void scanner_set_ast(Scanner *scanner, Sexp *ast) {
  sexp_delete(scanner->ast);
  scanner->ast = ast;
}
Sexp *scanner_get_ast(Scanner *scanner) {
  return scanner->ast;
}
void scanner_finish(Scanner *scanner, Sexp *ast) {
  scanner_set_ast(scanner, ast);
}
Sexp *scanner_token(Scanner *scanner) {
  return sexp_string(yyget_text(scanner->yyscan), yyget_leng(scanner->yyscan));
}
void scanner_register(Scanner *scanner, const char *symbol) {
  assert(!scanner_query(scanner, symbol));
  pool_insert(scanner->typedefs, symbol);
}
Bool scanner_query(Scanner *scanner, const char *symbol) {
  return pool_contains(scanner->typedefs, symbol);
}
