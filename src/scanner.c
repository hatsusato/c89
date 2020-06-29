#include "scanner.h"

#include <ctype.h>
#include <stdio.h>

#include "parser.tab.h"

void yyerror(yyscan_t scanner, const char *msg) {
  fprintf(stderr, "yyerror: %s: ", msg);
  msg = yyget_text(scanner);
  while (msg && *msg) {
    char c = *msg++;
    if (isprint(c)) {
      fprintf(stderr, "%c", c);
    } else {
      fprintf(stderr, "\\x%02x", (unsigned char)c);
    }
  }
  fprintf(stderr, "\n");
}

yyscan_t scanner_new(Result *result) {
  yyscan_t scanner = nil;
  const char *builtin_types[] = {
#define HANDLE(name) #name,
#include "enum/builtin.def"
#undef HANDLE
      nil};
  const char **it = builtin_types;
  Set *symbols = result_get_symbols(result);
  int ret = yylex_init_extra(result, &scanner);
  assert(ret == 0);
  while (it && *it) {
    set_string_insert(symbols, *it++);
  }
  return scanner;
}
void scanner_delete(yyscan_t scanner) {
  yylex_destroy(scanner);
}
int scanner_parse(yyscan_t scanner) {
  return yyparse(scanner);
}
void scanner_finish(yyscan_t scanner, AstList ast) {
  Result *result = yyget_extra(scanner);
  ast.sexp = result_set_sexp(result, ast.sexp);
  assert(!ast.sexp);
}
const char *scanner_get_text(yyscan_t scanner) {
  return yyget_text(scanner);
}
void scanner_insert_symbol(yyscan_t scanner, const char *str) {
  Result *result = yyget_extra(scanner);
  Set *symbols = result_get_symbols(result);
  set_string_insert(symbols, str);
}
Bool scanner_contains_symbol(yyscan_t scanner, const char *str) {
  Result *result = yyget_extra(scanner);
  Set *symbols = result_get_symbols(result);
  return set_string_contains(symbols, str);
}
Sexp *scanner_token(yyscan_t scanner) {
  return sexp_string(yyget_text(scanner), yyget_leng(scanner));
}
