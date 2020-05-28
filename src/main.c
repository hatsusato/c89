#include <stdio.h>

#include "parser.tab.h"

int main(void) {
  yyscan_t scanner;
  int ret = 0;
  Vector *seq = nil;
  yylex_init_extra(vector_new(1), &scanner);
  ret = yyparse(scanner);
  printf("return: %d\n", ret);
  seq = yyget_extra(scanner);
  vector_delete(&seq);
  yylex_destroy(scanner);
  return 0;
}
