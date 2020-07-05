#include "scanner.h"

#include <ctype.h>

#include "parser.tab.h"
#include "print.h"

void yyerror(yyscan_t scanner, const char *msg) {
  fprintf(stderr, "yyerror: %s: ", msg);
  print_verbatim(stderr, yyget_text(scanner), yyget_leng(scanner));
  fprintf(stderr, "\n");
}

static Bool check_tag(Sexp *ast, const char *tag) {
  assert(sexp_is_pair(ast) && sexp_is_list(ast));
  ast = sexp_car(ast);
  return sexp_eq(ast, tag);
}
static Bool is_typedef(Sexp *ast) {
  if (check_tag(ast, "storage-class-specifier")) {
    ast = sexp_at(ast, 1);
    return sexp_eq(ast, "typedef");
  } else {
    assert(check_tag(ast, "type-specifier") ||
           check_tag(ast, "type-qualifier"));
    return false;
  }
}
static Bool has_typedef(Sexp *ast) {
  assert(check_tag(ast, "declaration-specifiers"));
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    if (is_typedef(sexp_car(ast))) {
      return true;
    }
  }
  return false;
}
static const char *from_declarator(Sexp *ast);
static const char *from_direct_declarator(Sexp *ast) {
  Sexp *head = nil;
  assert(check_tag(ast, "direct-declarator"));
  head = sexp_at(ast, 1);
  if (check_tag(head, "identifier")) {
    head = sexp_at(head, 1);
    assert(sexp_is_string(head));
    return sexp_get(head);
  } else if (check_tag(head, "left-paren")) {
    return from_declarator(sexp_at(ast, 2));
  } else {
    return from_direct_declarator(head);
  }
}
static const char *from_declarator(Sexp *ast) {
  Sexp *head = nil;
  assert(check_tag(ast, "declarator"));
  head = sexp_at(ast, 1);
  if (check_tag(head, "pointer")) {
    return from_direct_declarator(sexp_at(ast, 2));
  } else {
    return from_direct_declarator(head);
  }
}
static const char *from_init_declarator(Sexp *ast) {
  assert(check_tag(ast, "init-declarator"));
  return from_declarator(sexp_at(ast, 1));
}
static void register_typedef(Set *symbols, Sexp *sexp) {
  assert(check_tag(sexp, "declaration"));
  if (has_typedef(sexp_at(sexp, 1))) {
    sexp = sexp_at(sexp, 2);
    assert(check_tag(sexp, "init-declarator-list"));
    for (sexp = sexp_cdr(sexp); sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
      const char *identifier = from_init_declarator(sexp_car(sexp));
      set_string_insert(symbols, identifier);
    }
  }
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
  while (*it) {
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
Sexp *scanner_token(yyscan_t scanner) {
  return sexp_string(yyget_text(scanner), yyget_leng(scanner));
}
void scanner_register_typedef(yyscan_t scanner, Sexp *sexp) {
  Result *result = yyget_extra(scanner);
  Set *symbols = result_get_symbols(result);
  register_typedef(symbols, sexp);
}
Bool scanner_query_typedef(yyscan_t scanner, const char *symbol) {
  Result *result = yyget_extra(scanner);
  Set *symbols = result_get_symbols(result);
  return set_string_contains(symbols, symbol);
}
