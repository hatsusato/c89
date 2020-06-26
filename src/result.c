#include "result.h"

#include <stdlib.h>

#include "utility.h"

struct struct_Result {
  List *ast;
};

Result *result_new(void) {
  Result *result = malloc(sizeof(Result));
  result->ast = nil;
  return result;
}
void result_delete(Result *result) {
  assert(result);
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
