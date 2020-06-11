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
static List *print_repeat(List *list, int indent, int repeat) {
  for (; 0 < repeat; --repeat) {
    list = print_line(list, indent);
  }
  return list;
}
static List *print_primary(List *list, int indent) {
  print_begin(indent);
  list = print_tag(list);
  list = print_repeat(list, indent + 1, 1);
  print_end();
  return list;
}
static List *print_postfix(List *list, int indent) {
  int repeat = 0;
  print_begin(indent);
  list = print_tag(list);
  switch (list_tag(list)) {
  case AST_ARRAY:
  case AST_CALL:
  case AST_PERIOD:
  case AST_ARROW:
    repeat = 2;
    break;
  case AST_INCREMENT:
  case AST_DECREMENT:
    repeat = 1;
    break;
  default:
    repeat = 0;
    break;
  }
  list = print_tag(list);
  list = print_repeat(list, indent + 1, repeat);
  print_end();
  return list;
}
static List *print_list(List *list, int indent) {
  print_begin(indent);
  list = print_tag(list);
  while (list) {
    if (AST_NIL == list_tag(list)) {
      list = list_next(list);
      break;
    }
    list = print_repeat(list, indent + 1, 1);
  }
  print_end();
  return list;
}
static List *print_unary(List *list, int indent) {
  print_begin(indent);
  list = print_tag(list);
  list = print_tag(list);
  list = print_repeat(list, indent + 1, 1);
  print_end();
  return list;
}
static List *print_case(List *list, int indent) {
  print_begin(indent);
  list = print_tag(list);
  list = print_repeat(list, indent + 1, 2);
  print_end();
  return list;
}
static List *print_binary(List *list, int indent) {
  print_begin(indent);
  list = print_tag(list);
  list = print_tag(list);
  list = print_repeat(list, indent + 1, 2);
  print_end();
  return list;
}
static List *print_conditional(List *list, int indent) {
  print_begin(indent);
  list = print_tag(list);
  list = print_repeat(list, indent + 1, 3);
  print_end();
  return list;
}
static List *print_expression(List *list, int indent) {
  print_begin(indent);
  list = print_tag(list);
  if (AST_COMMA == list_tag(list)) {
    list = list_next(list);
    list = print_repeat(list, indent + 1, 1);
  }
  list = print_repeat(list, indent + 1, 1);
  print_end();
  return list;
}
static List *print_constant(List *list, int indent) {
  print_begin(indent);
  list = print_tag(list);
  list = print_repeat(list, indent + 1, 1);
  print_end();
  return list;
}

void print_all(List *list) {
  while (list) {
    list = print_ast(list, 0);
    printf("\n");
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
  case AST_ARGUMENT_EXPRESSION_LIST:
    return print_list(list, indent);
  case AST_UNARY_EXPRESSION:
    return print_unary(list, indent);
  case AST_CAST_EXPRESSION:
    return print_case(list, indent);
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
  case AST_ASSIGNMENT_EXPRESSION:
    return print_binary(list, indent);
  case AST_CONDITIONAL_EXPRESSION:
    return print_conditional(list, indent);
  case AST_EXPRESSION:
    return print_expression(list, indent);
  case AST_CONSTANT_EXPRESSION:
    return print_constant(list, indent);
  default:
    printf("[%s]", ast_show(tag));
    return list_next(list);
  }
}
