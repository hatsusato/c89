#include "scanner.h"

#include "parser.tab.h"
#include "set.h"
#include "sexp.h"
#include "table.h"
#include "utility.h"

struct struct_Scanner {
  yyscan_t yyscan;
  Sexp *ast;
  Table *table;
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
  scanner->table = table_new();
  scanner->typedefs = set_new(typedefs_destructor, typedefs_compare);
  scanner_register(scanner, "__builtin_va_list", true);
  return scanner;
}
void scanner_delete(Scanner *scanner) {
  set_delete(scanner->typedefs);
  table_delete(scanner->table);
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
Table *scanner_table(Scanner *scanner) {
  return scanner->table;
}
void scanner_register(Scanner *scanner, const char *symbol, Bool flag) {
  SymbolSet *top = table_top(scanner->table);
  symbol_register(top, symbol, flag);
  if (flag) {
    Size size = strlen(symbol);
    char *buf;
    assert(!set_contains(scanner->typedefs, (ElemType)symbol));
    buf = UTILITY_MALLOC_ARRAY(char, size + 1);
    UTILITY_MEMCPY(char, buf, symbol, size);
    buf[size] = '\0';
    set_insert(scanner->typedefs, buf);
  }
}
