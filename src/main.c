#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "parser.tab.h"
#include "print.h"

void ast_list_free(List *list) {
  void *data = list_data(list);
  if (data) {
    vector_delete(data);
  }
}
void print_seq(yyscan_t scanner) {
  YY_EXTRA_TYPE extra = yyget_extra(scanner);
  List *list = extra.list;
  print_ast(list);
  list_delete(extra.list, ast_list_free);
}

int main(void) {
  yyscan_t scanner;
  YYSTYPE extra = {nil, nil};
  yylex_init_extra(extra, &scanner);
  printf("return: %d\n", yyparse(scanner));
  print_seq(scanner);
  yylex_destroy(scanner);
  return 0;
}
