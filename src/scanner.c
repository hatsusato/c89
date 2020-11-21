#include "scanner.h"

#include "parser.tab.h"
#include "pool.h"
#include "sexp.h"
#include "utility.h"

struct struct_Scanner {
  yyscan_t yyscan;
  Pool *symbols;
  Pool *typedefs;
  Sexp *ast;
};

Scanner *scanner_new(void) {
  Scanner *scanner = UTILITY_MALLOC(Scanner);
  int ret = yylex_init(&scanner->yyscan);
  assert(0 == ret);
  (void)ret;
  yyset_extra(scanner, scanner->yyscan);
  scanner->symbols = pool_new(pool_destruct);
  scanner->typedefs = pool_new(NULL);
  scanner->ast = sexp_nil();
  scanner_register(scanner, "__builtin_va_list");
  return scanner;
}
void scanner_delete(Scanner *scanner) {
  sexp_delete(scanner->ast);
  pool_delete(scanner->typedefs);
  pool_delete(scanner->symbols);
  yylex_destroy(scanner->yyscan);
  UTILITY_FREE(scanner);
}
int scanner_parse(Scanner *scanner) {
  return yyparse(scanner->yyscan);
}
Sexp *scanner_ast(Scanner *scanner) {
  return scanner->ast;
}
void scanner_finish(Scanner *scanner, Sexp *ast) {
  assert(sexp_is_nil(scanner->ast));
  scanner->ast = ast;
}
Sexp *scanner_token(Scanner *scanner) {
  const char *text = yyget_text(scanner->yyscan);
  Size leng = yyget_leng(scanner->yyscan);
  const char *token = pool_construct(text, leng);
  token = pool_insert(scanner->symbols, token);
  return sexp_symbol(token);
}
void scanner_register(Scanner *scanner, const char *symbol) {
  assert("redefinition of typedef" && !scanner_query(scanner, symbol));
  pool_insert(scanner->typedefs, symbol);
}
Bool scanner_query(Scanner *scanner, const char *symbol) {
  return pool_contains(scanner->typedefs, symbol);
}
