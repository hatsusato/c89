#include "result.h"

#include "scanner.h"
#include "set.h"
#include "sexp.h"
#include "table.h"
#include "utility.h"

struct struct_Result {
  Sexp *sexp;
  Set *symbols;
  Table *table;
};

static int result_set_compare(const ElemType *lhs, const ElemType *rhs) {
  return utility_str_cmp(*lhs, *rhs);
}

Result *result_new(void) {
  Result *result = UTILITY_MALLOC(Result);
  result->sexp = sexp_nil();
  result->symbols = set_new(NULL, result_set_compare);
  result->table = table_new();
  return result;
}
void result_delete(Result *result) {
  assert(result);
  sexp_delete(result->sexp);
  set_delete(result->symbols);
  table_delete(result->table);
  UTILITY_FREE(result);
}
int result_parse(Result *result) {
  yyscan_t scanner = scanner_new(result);
  int ret = scanner_parse(scanner);
  scanner_delete(scanner);
  return ret;
}
Table *result_get_table(Result *result) {
  assert(result);
  return result->table;
}
Sexp *result_set_sexp(Result *result, Sexp *sexp) {
  assert(result);
  UTILITY_SWAP(Sexp *, result->sexp, sexp);
  return sexp;
}
