#include <stdio.h>
#include <string.h>

#include "pretty.h"
#include "print.h"
#include "result.h"

void print_seq(Result *result) {
  List *ast = result_get_ast(result);
  print_ast(ast, 0);
  printf("\n");
  pretty_print(ast);
}

int main(void) {
  Result *result = result_new();
  int ret = result_parse(result);
  print_seq(result);
  result_delete(result);
  return ret;
}
