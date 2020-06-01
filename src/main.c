#include <stdio.h>
#include <string.h>

#include "parser.h"
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
  const char *cur = vector_begin(seq);
  const char *const end = vector_end(seq);
  while (cur < end) {
    int length = 0, i = 0;
    const char *text = nil;
    cur += ast_get_text(cur, &text, &length);
    printf("[%d:", length);
    for (i = 0; i < length; ++i) {
      printf("%c", text[i]);
    }
    printf("]\n");
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
