#include <stdio.h>
#include <string.h>

#include "parser.tab.h"

void print_seq(yyscan_t scanner) {
  const char *text = nil;
  Vector *seq = yyget_extra(scanner);
  int length = vector_length(seq);
  int i = 0;
  int id = 0;
  while (i < length) {
    text = vector_at(seq, i);
    id = *(int *)text;
    printf("%s:", show_token(id));
    text += sizeof(int);
    i += sizeof(int);
    printf("[%s]", text);
    i += strlen(text);
    ++i;
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
