#include "result.h"

#include "scanner.h"
#include "sexp.h"
#include "table.h"
#include "utility.h"

struct struct_Result {
  Sexp *sexp;
  Table *table;
};

Result *result_new(void) {
  Result *result = UTILITY_MALLOC(Result);
  result->sexp = sexp_nil();
  result->table = table_new();
  return result;
}
void result_delete(Result *result) {
  assert(result);
  sexp_delete(result->sexp);
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
Sexp *result_get_sexp(Result *result) {
  assert(result);
  return result->sexp;
}
void result_set_sexp(Result *result, Sexp *sexp) {
  assert(result);
  result->sexp = sexp;
}
