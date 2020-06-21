#include "print.h"

#include <ctype.h>
#include <stdio.h>

#include "ast.h"
#include "vector.h"

static void print_begin(int indent) {
  printf("\n");
  for (; 0 < indent; --indent) {
    printf("  ");
  }
  printf("(");
}
static void print_end(void) {
  printf(")");
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
static List *print_tag(List *list) {
  printf("%s:", ast_show(list_tag(list)));
  return list_next(list);
}
static List *print_token(List *list, int indent) {
  Vector *data = list_data(list);
  print_begin(indent);
  list = print_tag(list);
  print_data(data);
  print_end();
  return list;
}
static List *print_list(List *list, int indent) {
  print_begin(indent);
  list = print_tag(list);
  while (AST_NIL != list_tag(list)) {
    list = print_ast(list, indent + 1);
  }
  print_end();
  return list_next(list);
}
List *print_ast(List *list, int indent) {
  int tag = list_tag(list);
  list = list_next(list);
  switch (tag) {
  case AST_TOKEN:
    return print_token(list, indent);
  case AST_LIST:
    return print_list(list, indent);
  case AST_ARITY0:
    list = print_tag(list);
    return list;
  case AST_ARITY1:
    print_begin(indent);
    list = print_tag(list);
    list = print_ast(list, indent + 1);
    print_end();
    return list;
  case AST_ARITY2:
    print_begin(indent);
    list = print_tag(list);
    list = print_ast(list, indent + 1);
    list = print_ast(list, indent + 1);
    print_end();
    return list;
  case AST_ARITY3:
    print_begin(indent);
    list = print_tag(list);
    list = print_ast(list, indent + 1);
    list = print_ast(list, indent + 1);
    list = print_ast(list, indent + 1);
    print_end();
    return list;
  case AST_ARITY4:
    print_begin(indent);
    list = print_tag(list);
    list = print_ast(list, indent + 1);
    list = print_ast(list, indent + 1);
    list = print_ast(list, indent + 1);
    list = print_ast(list, indent + 1);
    print_end();
    return list;
  default:
    return print_tag(list);
  }
}
