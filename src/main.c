#include <stdio.h>
#include <string.h>

#include "parser.tab.h"

const char *consume_int(const char *cur, int *val) {
  *val = *(int *)cur;
  return cur + sizeof(*val);
}
const char *consume_text(const char *cur, const char **text) {
  *text = cur;
  return cur + strlen(cur) + 1;
}
const char *print_ast(const char *cur) {
  int arity = 0, tag = 0, i = 0;
  const char *text = nil;
  cur = consume_int(cur, &arity);
  cur = consume_int(cur, &tag);
  printf("[%d:", tag);
  if (arity == 0) {
    cur = consume_text(cur, &text);
    printf("%s", text);
  } else {
    for (i = 0; i < arity; ++i) {
      cur = print_ast(cur);
    }
  }
  printf("]");
  return cur;
}
void print_seq(yyscan_t scanner) {
  Vector *seq = yyget_extra(scanner);
  const char *text = vector_at(seq, 0);
  const char *const end = vector_at(seq, vector_length(seq));
  while (text < end) {
    text = print_ast(text);
  }
  printf("length: %d\n", vector_length(seq));
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
