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
void print_text(const char *text, int length) {
  int i = 0;
  for (i = 0; i < length; ++i) {
    printf("%c", text[i]);
  }
}
const char *print_ast(const char *cur) {
  int tag = 0, arity = 0, length = 0;
  const char *text = nil;
  cur = ast_get_int(cur, &tag);
  cur = ast_get_int(cur, &arity);
  printf("[%d:", tag);
  if (arity < 0) {
    cur = ast_get_text(cur, &text, &length);
    print_text(text, length);
  } else {
    int i = 0;
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
    cur = ast_print(cur);
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
