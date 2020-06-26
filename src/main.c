#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "pretty.h"
#include "print.h"
#include "string.h"

void ast_list_free(List *list) {
  void *data = list_data(list);
  if (data) {
    string_delete(data);
  }
}
void print_seq(yyscan_t scanner) {
  List *ast = scanner_get_ast(scanner);
  print_ast(ast, 0);
  printf("\n");
  pretty_print(ast);
  list_delete(ast, ast_list_free);
}

int main(void) {
  yyscan_t scanner = scanner_new();
  int ret = 0;
  ret = scanner_parse(scanner);
  print_seq(scanner);
  scanner_delete(scanner);
  return ret;
}
