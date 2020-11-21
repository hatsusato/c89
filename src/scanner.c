#include "scanner.h"

#include "parser.tab.h"
#include "set.h"
#include "sexp.h"
#include "utility.h"

struct struct_Scanner {
  yyscan_t yyscan;
  Sexp *ast;
  Set *typedefs;
};

static int typedefs_compare(const ElemType *lhs, const ElemType *rhs) {
  return strcmp(*lhs, *rhs);
}
static void typedefs_destructor(ElemType elem) {
  UTILITY_FREE(elem);
}

Scanner *scanner_new(void) {
  Scanner *scanner = UTILITY_MALLOC(Scanner);
  int ret = yylex_init(&scanner->yyscan);
  assert(0 == ret);
  (void)ret;
  yyset_extra(scanner, scanner->yyscan);
  scanner->ast = sexp_nil();
  scanner->typedefs = set_new(typedefs_destructor, typedefs_compare);
  scanner_register(scanner, "__builtin_va_list");
  return scanner;
}
void scanner_delete(Scanner *scanner) {
  set_delete(scanner->typedefs);
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
  Size size = strlen(symbol);
  char *buf;
  assert(!set_contains(scanner->typedefs, (ElemType)symbol));
  buf = UTILITY_MALLOC_ARRAY(char, size + 1);
  UTILITY_MEMCPY(char, buf, symbol, size);
  buf[size] = '\0';
  set_insert(scanner->typedefs, buf);
}
Bool scanner_query(Scanner *scanner, const char *symbol) {
  return set_contains(scanner->typedefs, (ElemType)symbol);
}
