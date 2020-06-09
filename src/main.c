#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "parser.tab.h"

void print_seq(yyscan_t scanner) {
  Vector *seq = yyget_extra(scanner);
  const char *cur = vector_begin(seq);
  const char *const end = vector_end(seq);
  while (cur < end) {
    cur = ast_vec_print(cur);
    printf("\n");
  }
  vector_delete(&seq);
}

int main(void) {
  yyscan_t scanner;
  yylex_init_extra(vector_new(1), &scanner);
  printf("return: %d\n", yyparse(scanner));
  print_seq(scanner);
  yylex_destroy(scanner);
  return 0;
}
