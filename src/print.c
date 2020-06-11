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
static void print_indent(int indent) {
  int i = 0;
  if (indent < 0) {
    indent = 0;
  }
  for (i = 0; i < indent; ++i) {
    printf("  ");
  }
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
static List *print_token(List *list, int indent) {
  print_indent(indent);
  print_begin();
  print_tag(list_tag(list));
  print_data(list_data(list));
  print_end();
  return list_next(list);
}
static List *print_primary(List *list, int indent) {
  print_indent(indent);
  print_begin();
  print_tag(list_tag(list));
  print_newline();
  list = list_next(list);
  list = print_ast(list, indent + 1);
  print_end();
  return list;
}
static List *print_postfix(List *list, int indent) {
  print_indent(indent);
  print_begin();
  print_tag(list_tag(list));
  list = list_next(list);
  print_tag(list_tag(list));
  print_newline();
  switch (list_tag(list)) {
  case AST_ARRAY:
  case AST_CALL:
  case AST_PERIOD:
  case AST_ARROW:
    list = list_next(list);
    list = print_ast(list, indent + 1);
    print_newline();
    list = print_ast(list, indent + 1);
    break;
  case AST_INCREMENT:
  case AST_DECREMENT:
    list = list_next(list);
    list = print_ast(list, indent + 1);
    break;
  }
  print_end();
  return list;
}

void print_all(List *list) {
  while (list) {
    list = print_ast(list, 0);
    print_newline();
  }
}
List *print_ast(List *list, int indent) {
  int tag = list_tag(list);
  switch (tag) {
  case AST_IDENTIFIER:
  case AST_FLOATING_CONSTANT:
  case AST_INTEGER_CONSTANT:
  case AST_ENUMERATION_CONSTANT:
  case AST_CHARACTER_CONSTANT:
  case AST_STRING_LITERAL:
    return print_token(list, indent);
  case AST_PRIMARY_EXPRESSION:
    return print_primary(list, indent);
  case AST_POSTFIX_EXPRESSION:
    return print_postfix(list, indent);
  default:
    print_indent(indent);
    printf("[%s]", ast_show(tag));
    return list_next(list);
  }
}
