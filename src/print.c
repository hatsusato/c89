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
static List *print_token(List *list) {
  print_begin();
  print_tag(list_tag(list));
  print_data(list_data(list));
  print_end();
  print_newline();
  return list_next(list);
}
static List *print_primary(List *list) {
  print_begin();
  print_tag(list_tag(list));
  list = list_next(list);
  print_ast(list);
  print_end();
  print_newline();
  return list;
}

void print_all(List *list) {
  while (list) {
    list = print_ast(list);
  }
}
List *print_ast(List *list) {
  int tag = list_tag(list);
  switch (tag) {
  case AST_IDENTIFIER:
  case AST_FLOATING_CONSTANT:
  case AST_INTEGER_CONSTANT:
  case AST_ENUMERATION_CONSTANT:
  case AST_CHARACTER_CONSTANT:
  case AST_STRING_LITERAL:
    return print_token(list);
  case AST_PRIMARY_EXPRESSION:
    return print_primary(list);
  default:
    printf("[%s]\n", ast_show(tag));
    return list_next(list);
  }
}
