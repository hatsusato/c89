#include "result.h"

#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "table.h"
#include "utility.h"

struct struct_Result {
  Sexp *sexp;
  Set *symbols;
  SymbolTable *table;
};

static int result_set_compare(const SetElem *lhs, const SetElem *rhs) {
  return strcmp(*lhs, *rhs);
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

Result *result_new(void) {
  Result *result = malloc(sizeof(Result));
  result->sexp = sexp_nil();
  result->symbols = set_new(result_set_compare);
  result->table = table_new();
  return result;
}
void result_delete(Result *result) {
  assert(result);
  sexp_delete(result->sexp);
  set_delete(result->symbols);
  table_delete(result->table);
  free(result);
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
  SWAP(Sexp *, result->sexp, sexp);
  return sexp;
}
void result_push_scope(Result *result) {
  assert(result);
  table_push(result->table);
}
void result_pop_scope(Result *result) {
  assert(result);
  table_pop(result->table);
}
