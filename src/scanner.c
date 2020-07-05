#include "scanner.h"

#include <ctype.h>

#include "parser.tab.h"
#include "print.h"

void yyerror(yyscan_t scanner, const char *msg) {
  fprintf(stderr, "yyerror: %s: ", msg);
  print_verbatim(stderr, yyget_text(scanner), yyget_leng(scanner));
  fprintf(stderr, "\n");
}

static Bool is_typedef(Sexp *ast) {
  assert(sexp_check_tag(ast, "declaration-specifiers"));
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    Sexp *specifier = sexp_car(ast);
    if (sexp_check_tag(specifier, "storage-class-specifier")) {
      specifier = sexp_at(specifier, 1);
      if (sexp_eq(specifier, "typedef")) {
        return true;
      } else {
        continue;
      }
    }
    assert(sexp_check_tag(specifier, "type-specifier") ||
           sexp_check_tag(specifier, "type-qualifier"));
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
static Sexp *from_declarator(Sexp *ast);
static Sexp *from_direct_declarator(Sexp *ast) {
  Sexp *next = nil;
  assert(sexp_check_tag(ast, "direct-declarator"));
  next = sexp_at(ast, 1);
  if (sexp_check_tag(next, "identifier")) {
    return next;
  } else if (sexp_check_tag(next, "left-paren")) {
    next = sexp_at(ast, 2);
    return from_declarator(next);
  } else {
    return from_direct_declarator(next);
  }
}
static Sexp *from_declarator(Sexp *ast) {
  Sexp *next = nil;
  assert(sexp_check_tag(ast, "declarator"));
  next = sexp_at(ast, 1);
  if (sexp_check_tag(next, "pointer")) {
    next = sexp_at(ast, 2);
  }
  return from_direct_declarator(next);
}
static Sexp *from_init_declarator(Sexp *ast) {
  assert(sexp_check_tag(ast, "init-declarator"));
  ast = sexp_at(ast, 1);
  return from_declarator(ast);
}
static void register_typedef(Set *symbols, Sexp *sexp) {
  assert(sexp_check_tag(sexp, "declaration"));
  if (is_typedef(sexp_at(sexp, 1))) {
    sexp = sexp_at(sexp, 2);
    assert(sexp_check_tag(sexp, "init-declarator-list"));
    for (sexp = sexp_cdr(sexp); sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
      Sexp *identifier = from_init_declarator(sexp_car(sexp));
      assert(sexp_check_tag(identifier, "identifier"));
      identifier = sexp_at(identifier, 1);
      assert(sexp_is_string(identifier));
      set_string_insert(symbols, sexp_get_string(identifier));
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
void scanner_register_typedef(yyscan_t scanner, Sexp *sexp) {
  Result *result = yyget_extra(scanner);
  Set *symbols = result_get_symbols(result);
  register_typedef(symbols, sexp);
}
