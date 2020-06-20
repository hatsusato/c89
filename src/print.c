#include "print.h"

#include <ctype.h>
#include <stdio.h>

#include "ast.h"
#include "vector.h"

static void print_begin(int indent) {
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
static List *print_token(List *list) {
  Vector *data = list_data(list);
  list = print_tag(list);
  print_data(data);
  print_end();
  return list;
}
static List *print_line(List *list, int indent) {
  printf("\n");
  return print_ast(list, indent);
}
static List *print_repeat(List *list, int indent, int repeat) {
  list = print_tag(list);
  for (; 0 < repeat; --repeat) {
    list = print_line(list, indent + 1);
  }
  print_end();
  return list;
}
List *print_list(List *list, int indent) {
  if (AST_LIST == list_tag(list)) {
    list = list_next(list);
  }
  list = print_tag(list);
  while (list) {
    if (AST_NIL == list_tag(list)) {
      list = list_next(list);
      break;
    }
    list = print_line(list, indent + 1);
  }
  print_end();
  return list;
}
List *print_ast(List *list, int indent) {
  print_begin(indent);
  switch (list_tag(list)) {
    /* List */
  case AST_LIST:
    return print_list(list, indent);
    /* Lexical elements */
#define HANDLE(name, str) case AST_##name:
#include "enum/keyword.def"
#include "enum/symbol.def"
#undef HANDLE
    return print_repeat(list, indent, 0);
  case AST_IDENTIFIER:
  case AST_FLOATING_CONSTANT:
  case AST_INTEGER_CONSTANT:
  case AST_ENUMERATION_CONSTANT:
  case AST_CHARACTER_CONSTANT:
  case AST_STRING_LITERAL:
    return print_token(list);
    /* Declarations */
  case AST_PARAMETER_DECLARATION:
    return print_repeat(list, indent, 2);
  case AST_TYPE_NAME:
    return print_repeat(list, indent, 2);
  case AST_ABSTRACT_DECLARATOR:
    return print_repeat(list, indent, 2);
  case AST_DIRECT_ABSTRACT_DECLARATOR:
    return print_repeat(list, indent, 2);
  case AST_DIRECT_ABSTRACT_DECLARATOR_SUFFIX:
    list = print_tag(list);
    return print_repeat(list, indent, 1);
  case AST_TYPEDEF_NAME:
    return print_repeat(list, indent, 1);
  case AST_INITIALIZER:
    return print_repeat(list, indent, 1);
  case AST_STATEMENT:
    return print_repeat(list, indent, 1);
  case AST_LABELED_STATEMENT:
    list = print_tag(list);
    return print_repeat(list, indent, 2);
  case AST_COMPOUND_STATEMENT:
    return print_repeat(list, indent, 2);
  case AST_EXPRESSION_STATEMENT:
    return print_repeat(list, indent, 1);
  case AST_SELECTION_STATEMENT:
    list = print_tag(list);
    return print_repeat(list, indent, 3);
  case AST_ITERATION_STATEMENT:
    list = print_tag(list);
    return print_repeat(list, indent, 2);
  case AST_ITERATION_STATEMENT_FOR:
    return print_repeat(list, indent, 3);
  case AST_JUMP_STATEMENT:
    list = print_tag(list);
    return print_repeat(list, indent, 1);
  case AST_EXTERNAL_DECLARATION:
    return print_repeat(list, indent, 1);
  case AST_FUNCTION_DEFINITION:
    return print_repeat(list, indent, 4);
  case AST_NIL:
    printf(")");
    return list_next(list);
  case AST_ARITY0:
    list = list_next(list);
    list = print_tag(list);
    print_end();
    return list;
  case AST_ARITY1:
    list = list_next(list);
    list = print_tag(list);
    list = print_line(list, indent + 1);
    print_end();
    return list;
  case AST_ARITY2:
    list = list_next(list);
    list = print_tag(list);
    list = print_line(list, indent + 1);
    list = print_line(list, indent + 1);
    print_end();
    return list;
  case AST_ARITY3:
    list = list_next(list);
    list = print_tag(list);
    list = print_line(list, indent + 1);
    list = print_line(list, indent + 1);
    list = print_line(list, indent + 1);
    print_end();
    return list;
  default:
    return print_tag(list);
  }
}
