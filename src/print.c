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
static void print_data(Vector *data) {
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
    Vector *data = list_data(list);
    switch (tag) {
    case AST_IDENTIFIER:
    case AST_FLOATING_CONSTANT:
    case AST_INTEGER_CONSTANT:
    case AST_ENUMERATION_CONSTANT:
    case AST_CHARACTER_CONSTANT:
    case AST_STRING_LITERAL:
      print_begin();
      print_tag(tag);
      print_data(data);
      print_end();
      print_newline();
      break;
    default:
      printf("[%s]\n", ast_show(tag));
    }
    list = list_next(list);
  }
}
