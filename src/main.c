#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "parser.tab.h"
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
  YY_EXTRA_TYPE extra = yyget_extra(scanner);
  List *list = extra.list;
  print_ast(list, 0);
  printf("\n");
  pretty_print(list);
  list_delete(extra.list, ast_list_free);
}

int main(void) {
  yyscan_t scanner = scanner_new();
  int ret = 0;
  ret = yyparse(scanner);
  print_seq(scanner);
  scanner_delete(scanner);
  return ret;
}
