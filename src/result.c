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
