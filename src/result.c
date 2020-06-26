#include "result.h"

#include <stdlib.h>

#include "string.h"
#include "utility.h"

struct struct_Result {
  List *ast;
};

static void result_ast_data_free(List *ast) {
  String *data = list_data(ast);
  if (data) {
    string_delete(data);
  }
}

Result *result_new(void) {
  Result *result = malloc(sizeof(Result));
  result->ast = nil;
  return result;
}
void result_delete(Result *result) {
  assert(result);
  list_delete(result->ast, result_ast_data_free);
  free(result);
}
List *result_get_ast(Result *result) {
  assert(result);
  return result->ast;
}
void result_set_ast(Result *result, List *ast) {
  assert(result);
  result->ast = ast;
}
