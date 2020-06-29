#include "result.h"

#include <stdlib.h>

#include "scanner.h"
#include "string.h"
#include "utility.h"

struct struct_Result {
  Sexp *sexp;
  List *ast;
  Set *symbols;
};

static void result_ast_data_free(List *ast) {
  String *data = list_data(ast);
  if (data) {
    string_delete(data);
  }
}

Result *result_new(void) {
  Result *result = malloc(sizeof(Result));
  result->sexp = sexp_nil();
  result->ast = nil;
  result->symbols = set_new();
  return result;
}
void result_delete(Result *result) {
  assert(result);
  sexp_delete(result->sexp);
  list_delete(result->ast, result_ast_data_free);
  set_delete(result->symbols);
  free(result);
}
int result_parse(Result *result) {
  yyscan_t scanner = scanner_new(result);
  int ret = scanner_parse(scanner);
  scanner_delete(scanner);
  return ret;
}
List *result_get_ast(Result *result) {
  assert(result);
  return result->ast;
}
void result_set_ast(Result *result, List *ast) {
  assert(result);
  result->ast = ast;
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
