#include <stdio.h>
#include <string.h>

#include "parser.tab.h"

void print_seq(yyscan_t scanner) {
  Vector *seq = yyget_extra(scanner);
  const char *text = vector_at(seq, 0);
  const char *const end = vector_at(seq, vector_length(seq));
  int id = 0;
  while (text < end) {
    id = *(int *)text;
    printf("%s:", show_token(id));
    text += sizeof(int);
    printf("[%s]", text);
    text += strlen(text) + 1;
  }
  printf("\n");
  vector_delete(&seq);
}

int main(void) {
  yyscan_t scanner;
  int ret = 0;
  yylex_init_extra(vector_new(1), &scanner);
  ret = yyparse(scanner);
  print_seq(scanner);
  printf("return: %d\n", ret);
  yylex_destroy(scanner);
  return 0;
}
