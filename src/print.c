#include "print.h"

#include <ctype.h>
#include <stdio.h>

#include "ast.h"
#include "vector.h"

static void print_begin(void) {
  printf("[");
}
static void print_end(void) {
  printf("]");
}
static void print_newline(void) {
  printf("\n");
}
static void print_tag(int tag) {
  printf("%s:", ast_show(tag));
}
static void print_token(Vector *data) {
  const char *text = vector_begin(data);
  int leng = vector_length(data);
  int i = 0;
  for (i = 0; i < leng; ++i) {
    char c = text[i];
    if (isprint(c)) {
      printf("%c", c);
    } else {
      printf("\\x%02x", c);
    }
  }
}

void print_ast(List *list) {
  while (list) {
    int tag = list_tag(list);
    switch (tag) {
    default:
      printf("[%s]\n", ast_show(tag));
    }
    list = list_next(list);
  }
}
