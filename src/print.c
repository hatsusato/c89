#include "print.h"

#include <ctype.h>
#include <stdio.h>

#include "ast.h"
#include "vector.h"

static void print_begin(int tag, int indent) {
  if (AST_ARITY0 == tag) {
    return;
  }
  printf("\n");
  for (; 0 < indent; --indent) {
    printf("  ");
  }
  printf("(");
}
static void print_end(int tag) {
  if (AST_ARITY0 == tag) {
    return;
  }
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
  list = print_tag(list);
  print_data(data);
  return list;
}
static List *print_list(List *list, int indent) {
  list = print_tag(list);
  while (AST_NIL != list_tag(list)) {
    list = print_ast(list, indent + 1);
  }
  return list_next(list);
}
List *print_ast(List *list, int indent) {
  int tag = list_tag(list);
  list = list_next(list);
  print_begin(tag, indent);
  switch (tag) {
  case AST_TOKEN:
    list = print_token(list, indent);
    break;
  case AST_LIST:
    list = print_list(list, indent);
    break;
  case AST_ARITY0:
    list = print_tag(list);
    break;
  case AST_ARITY1:
    list = print_tag(list);
    list = print_ast(list, indent + 1);
    break;
  case AST_ARITY2:
    list = print_tag(list);
    list = print_ast(list, indent + 1);
    list = print_ast(list, indent + 1);
    break;
  case AST_ARITY3:
    list = print_tag(list);
    list = print_ast(list, indent + 1);
    list = print_ast(list, indent + 1);
    list = print_ast(list, indent + 1);
    break;
  case AST_ARITY4:
    list = print_tag(list);
    list = print_ast(list, indent + 1);
    list = print_ast(list, indent + 1);
    list = print_ast(list, indent + 1);
    list = print_ast(list, indent + 1);
    break;
  default:
    assert(0);
  }
  print_end(tag);
  return list;
}
