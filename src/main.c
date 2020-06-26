#include <stdio.h>
#include <string.h>

#include "pretty.h"
#include "print.h"
#include "result.h"
#include "scanner.h"

void print_seq(Result *result) {
  List *ast = result_get_ast(result);
  print_ast(ast, 0);
  printf("\n");
  pretty_print(ast);
}

Result *parse() {
  Result *result = result_new();
  yyscan_t scanner = scanner_new(result);
  scanner_parse(scanner);
  scanner_delete(scanner);
  return result;
}

int main(void) {
  Result *result = parse();
  print_seq(result);
  result_delete(result);
  return 0;
}
