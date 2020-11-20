#include "scanner.h"

#include "parser.tab.h"
#include "sexp.h"
#include "utility.h"

struct struct_Scanner {
  yyscan_t yyscan;
  Sexp *ast;
};

Scanner *scanner_new(void) {
  Scanner *scanner = UTILITY_MALLOC(Scanner);
  int ret = yylex_init(&scanner->yyscan);
  assert(0 == ret);
  (void)ret;
  yyset_extra(scanner, scanner->yyscan);
  scanner->ast = NULL;
  return scanner;
}
void scanner_delete(Scanner *scanner) {
  sexp_delete(scanner->ast);
  yylex_destroy(scanner->yyscan);
  UTILITY_FREE(scanner);
}
int scanner_parse(Scanner *scanner) {
  return yyparse(scanner->yyscan);
}
void scanner_set_ast(Scanner *scanner, Sexp *ast) {
  scanner->ast = ast;
}
Sexp *scanner_get_ast(Scanner *scanner) {
  return scanner->ast;
}
