#include "result.h"

#include "scanner.h"
#include "set.h"
#include "sexp.h"
#include "table.h"
#include "utility.h"

struct struct_Result {
  Sexp *sexp;
  Set *symbols;
};

static int result_set_compare(const ElemType *lhs, const ElemType *rhs) {
  return utility_str_cmp(*lhs, *rhs);
}
static Bool check_tag(Sexp *ast, const char *tag) {
  return sexp_is_pair(ast) && sexp_is_list(ast) && sexp_eq(sexp_car(ast), tag);
}
static Bool is_typedef(Sexp *ast) {
  assert(check_tag(ast, "declaration-specifiers"));
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    Sexp *spec = sexp_car(ast);
    assert(check_tag(spec, "storage-class-specifier") ||
           check_tag(spec, "type-specifier") ||
           check_tag(spec, "type-qualifier"));
    if (check_tag(spec, "storage-class-specifier") &&
        sexp_eq(sexp_at(spec, 1), "typedef")) {
      return true;
    }
  }
  return false;
}
static const char *from_declarator(Sexp *ast);
static const char *from_identifier(Sexp *ast) {
  assert(check_tag(ast, "identifier"));
  ast = sexp_at(ast, 1);
  assert(sexp_is_string(ast));
  return sexp_get(ast);
}
static const char *from_direct_declarator(Sexp *ast) {
  assert(check_tag(ast, "direct-declarator"));
  ast = sexp_cdr(ast);
  if (check_tag(ast, "(")) {
    return from_declarator(sexp_at(ast, 1));
  } else {
    ast = sexp_car(ast);
    if (check_tag(ast, "identifier")) {
      return from_identifier(ast);
    } else {
      return from_direct_declarator(ast);
    }
  }
}
static const char *from_declarator(Sexp *ast) {
  assert(check_tag(ast, "declarator"));
  ast = sexp_at(ast, sexp_length(ast) - 1);
  return from_direct_declarator(ast);
}
static const char *from_init_declarator(Sexp *ast) {
  assert(check_tag(ast, "init-declarator"));
  return from_declarator(sexp_at(ast, 1));
}

Result *result_new(void) {
  Result *result = UTILITY_MALLOC(Result);
  result->sexp = sexp_nil();
  result->symbols = set_new(NULL, result_set_compare);
  return result;
}
void result_delete(Result *result) {
  assert(result);
  sexp_delete(result->sexp);
  set_delete(result->symbols);
  UTILITY_FREE(result);
}
int result_parse(Result *result) {
  yyscan_t scanner = scanner_new(result);
  int ret = scanner_parse(scanner);
  scanner_delete(scanner);
  return ret;
}
Set *result_get_symbols(Result *result) {
  assert(result);
  return result->symbols;
}
Sexp *result_set_sexp(Result *result, Sexp *sexp) {
  assert(result);
  UTILITY_SWAP(Sexp *, result->sexp, sexp);
  return sexp;
}
void result_push_scope(Result *result) {
  assert(result);
}
void result_pop_scope(Result *result) {
  assert(result);
}
void result_register(Result *result, Sexp *decl) {
  assert(result);
  assert(check_tag(decl, "declaration"));
}
Bool result_query(Result *result, const char *symbol) {
  assert(result);
}
