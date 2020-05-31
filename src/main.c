#include <stdio.h>
#include <string.h>

#include "parser.tab.h"

int consume_id(const char **text) {
  int token = *(int *)*text;
  *text += sizeof(int);
  return token;
}
const char *consume_text(const char **text) {
  const char *head = *text;
  *text += strlen(*text) + 1;
  return head;
}
void print_text(const char **text) {
  int token = consume_id(text);
  const char *const head = consume_text(text);
  printf("[%d:%s]", token, head);
  switch (token) {
  case PUNCTUATOR_SEMICOLON:
  case PUNCTUATOR_LEFT_BRACE:
  case PUNCTUATOR_RIGHT_BRACE:
    printf("\n");
  }
}
void print_seq(yyscan_t scanner) {
  Vector *seq = yyget_extra(scanner);
  const char *text = vector_at(seq, 0);
  const char *const end = vector_at(seq, vector_length(seq));
  while (text < end) {
    print_text(&text);
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
