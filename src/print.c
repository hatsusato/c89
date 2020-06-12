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
static List *print_token(List *list, int indent) {
  Vector *data = list_data(list);
  print_begin(indent);
  list = print_tag(list);
  print_data(data);
  print_end();
  return list;
}
static List *print_line(List *list, int indent) {
  printf("\n");
  return print_ast(list, indent);
}
static List *print_repeat(List *list, int indent, int tag_count,
                          int repeat_count) {
  print_begin(indent);
  for (; 0 < tag_count; --tag_count) {
    list = print_tag(list);
  }
  for (; 0 < repeat_count; --repeat_count) {
    list = print_line(list, indent + 1);
  }
  print_end();
  return list;
}
static List *print_nil(List *list, int indent) {
  print_repeat(list, indent, 0, 0);
  return list_next(list);
}
static List *print_list(List *list, int indent) {
  print_begin(indent);
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
static List *print_postfix(List *list, int indent) {
  int arity = 0;
  switch (list_tag(list_next(list))) {
  case AST_ARRAY:
  case AST_CALL:
  case AST_PERIOD:
  case AST_ARROW:
    arity = 2;
    break;
  case AST_INCREMENT:
  case AST_DECREMENT:
    arity = 1;
    break;
  }
  return print_repeat(list, indent, 2, arity);
}
static List *print_expression(List *list, int indent) {
  int arity = 1;
  switch (list_tag(list_next(list))) {
  case AST_COMMA:
    arity = 2;
    break;
  }
  return print_repeat(list, indent, arity, arity);
}

void print_all(List *list) {
  while (list) {
    list = print_ast(list, 0);
    printf("\n");
  }
}
List *print_ast(List *list, int indent) {
  switch (list_tag(list)) {
    /* Lexical elements */
  case AST_IDENTIFIER:
  case AST_FLOATING_CONSTANT:
  case AST_INTEGER_CONSTANT:
  case AST_ENUMERATION_CONSTANT:
  case AST_CHARACTER_CONSTANT:
  case AST_STRING_LITERAL:
    return print_token(list, indent);
    /* List */
  case AST_ARGUMENT_EXPRESSION_LIST:
  case AST_DECLARATION_SPECIFIERS:
  case AST_INIT_DECLARATOR_LIST:
    return print_list(list, indent);
  case AST_NIL:
    return print_nil(list, indent);
    /* Expressions */
  case AST_PRIMARY_EXPRESSION:
    return print_repeat(list, indent, 1, 1);
  case AST_POSTFIX_EXPRESSION:
    return print_postfix(list, indent);
  case AST_UNARY_EXPRESSION:
    return print_repeat(list, indent, 2, 1);
  case AST_CAST_EXPRESSION:
    return print_repeat(list, indent, 1, 2);
  case AST_MULTIPLICATIVE_EXPRESSION:
  case AST_ADDITIVE_EXPRESSION:
  case AST_SHIFT_EXPRESSION:
  case AST_RELATIONAL_EXPRESSION:
  case AST_EQUALITY_EXPRESSION:
  case AST_AND_EXPRESSION:
  case AST_EXCLUSIVE_OR_EXPRESSION:
  case AST_INCLUSIVE_OR_EXPRESSION:
  case AST_LOGICAL_AND_EXPRESSION:
  case AST_LOGICAL_OR_EXPRESSION:
    return print_repeat(list, indent, 2, 2);
  case AST_CONDITIONAL_EXPRESSION:
    return print_repeat(list, indent, 1, 3);
  case AST_ASSIGNMENT_EXPRESSION:
    return print_repeat(list, indent, 2, 2);
  case AST_EXPRESSION:
    return print_expression(list, indent);
  case AST_CONSTANT_EXPRESSION:
    return print_repeat(list, indent, 1, 1);
    /* Declarations */
  case AST_DECLARATION:
    return print_repeat(list, indent, 1, 2);
  case AST_INIT_DECLARATOR:
    return print_repeat(list, indent, 1, 2);
  case AST_STORAGE_CLASS_SPECIFIER:
    return print_repeat(list, indent, 2, 0);
  default:
    printf("[%s]", ast_show(list_tag(list)));
    return list_next(list);
  }
}
