#include <stdio.h>

#include "parser.tab.h"

int main(void) {
  yyscan_t scanner;
  int ret = 0;
  yylex_init(&scanner);
  ret = yyparse(scanner);
  printf("return: %d\n", ret);
  yylex_destroy(scanner);
  return 0;
}
