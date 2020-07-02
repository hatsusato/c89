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
void scanner_finish(yyscan_t scanner, Sexp *sexp) {
  Result *result = yyget_extra(scanner);
  sexp = result_set_sexp(result, sexp);
  assert(!sexp);
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
static Bool is_typedef(Sexp *sexp) {
  assert(sexp_check_tag(sexp, "declaration"));
  sexp = sexp_at(sexp, 1);
  assert(sexp_check_tag(sexp, "declaration-specifiers"));
  for (sexp = sexp_cdr(sexp); sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
    Sexp *spec = sexp_car(sexp);
    if (sexp_check_tag(spec, "storage-class-specifier")) {
      return sexp_eq(sexp_at(spec, 1), "typedef");
    }
  }
  return false;
}
static Sexp *get_identifier(Sexp *decl) {
  assert(sexp_check_tag(decl, "declarator"));
  decl = sexp_last(decl);
  assert(sexp_check_tag(decl, "direct-declarator"));
  switch (sexp_length(decl)) {
  case 2:
    return sexp_at(decl, 1);
  case 4:
    return get_identifier(sexp_at(decl, 2));
  default:
    return sexp_nil();
  }
}
void scanner_register_typedef(yyscan_t scanner, Sexp *sexp) {
  assert(sexp_check_tag(sexp, "declaration"));
  if (is_typedef(sexp)) {
    sexp = sexp_at(sexp, 2);
    assert(sexp_check_tag(sexp, "init-declarator-list"));
    for (sexp = sexp_cdr(sexp); sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
      Sexp *id = sexp_car(sexp);
      assert(sexp_check_tag(id, "init-declarator"));
      id = get_identifier(sexp_at(id, 1));
      if (sexp_check_tag(id, "identifier")) {
        id = sexp_at(id, 1);
        assert(sexp_is_string(id));
        scanner_insert_symbol(scanner, sexp_get_string(id));
      }
    }
  }
}
