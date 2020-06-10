#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "parser.tab.h"

void print_seq(yyscan_t scanner) {
  YY_EXTRA_TYPE extra = yyget_extra(scanner);
  Vector *seq = extra.vec;
  List *list = extra.list;
  const char *cur = vector_begin(seq);
  const char *const end = vector_end(seq);
  while (cur < end) {
    cur = ast_vec_print(cur);
    printf("\n");
  }
  vector_delete(seq);
  while (list) {
    printf("[%s]\n", ast_show(list_tag(list)));
    if (list_data(list)) {
      vector_delete(list_data(list));
    }
    list = list_next(list);
  }
  list_delete(extra.list);
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
