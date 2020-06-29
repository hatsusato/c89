#include "print.h"

#include <ctype.h>
#include <stdio.h>

#include "ast.h"
#include "string.h"

static void print_begin(int indent) {
  printf("\n");
  print_indent(indent * 2);
  printf("(");
}
static void print_end(void) {
  printf(")");
}
static List *print_tag(List *list) {
  printf("%s:", ast_show(list_tag(list)));
  return list_next(list);
}
static List *print_token(List *list) {
  assert(AST_DATA == list_tag(list));
  return print_data(list);
}
static List *print_list(List *list, int indent) {
  while (AST_NIL != list_tag(list)) {
    list = print_ast(list, indent);
  }
  return list_next(list);
}

void print_indent(int indent) {
  for (; 0 < indent; --indent) {
    printf(" ");
  }
}
List *print_data(List *list) {
  String *data = list_data(list);
  const char *text = string_begin(data);
  int leng = string_length(data);
  int i = 0;
  for (i = 0; i < leng; ++i) {
    char c = text[i];
    if (isprint(c)) {
      printf("%c", c);
    } else {
      printf("\\x%02x", c);
    }
  }
  return list_next(list);
}
List *print_ast(List *list, int indent) {
  int tag = list_tag(list);
  list = list_next(list);
  if (AST_ARITY0 == tag) {
    return print_tag(list);
  }
  print_begin(indent);
  list = print_tag(list);
  switch (tag) {
  case AST_TOKEN:
    list = print_token(list);
    break;
  case AST_LIST:
    list = print_list(list, indent + 1);
    break;
  case AST_ARITY1:
    goto case_arity1;
  case AST_ARITY2:
    goto case_arity2;
  case AST_ARITY3:
    goto case_arity3;
  case AST_ARITY4:
    goto case_arity4;
  case_arity4:
    list = print_ast(list, indent + 1);
  case_arity3:
    list = print_ast(list, indent + 1);
  case_arity2:
    list = print_ast(list, indent + 1);
  case_arity1:
    list = print_ast(list, indent + 1);
    break;
  default:
    assert(0);
  }
  print_end();
  return list;
}

List *print_consume(List *ast) {
  int tag = list_tag(ast);
  ast = list_next(ast);
  ast = list_next(ast);
  switch (tag) {
  case AST_TOKEN:
    ast = list_next(ast);
    break;
  case AST_LIST:
    while (AST_NIL != list_tag(ast)) {
      ast = print_consume(ast);
    }
    ast = list_next(ast);
    break;
  case AST_ARITY0:
    goto case_arity0;
  case AST_ARITY1:
    goto case_arity1;
  case AST_ARITY2:
    goto case_arity2;
  case AST_ARITY3:
    goto case_arity3;
  case AST_ARITY4:
    goto case_arity4;
  case_arity4:
    ast = print_consume(ast);
  case_arity3:
    ast = print_consume(ast);
  case_arity2:
    ast = print_consume(ast);
  case_arity1:
    ast = print_consume(ast);
  case_arity0:
    break;
  default:
    assert(0);
  }
  return ast;
}
