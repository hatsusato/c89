#include "print.h"

#include <stdio.h>

#include "ast.h"

static void print_begin(void) {
  printf("[");
}
static void print_end(void) {
  printf("]");
}
static void print_newline(void) {
  printf("\n");
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
