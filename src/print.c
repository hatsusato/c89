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
static List *print_list(List *list, int indent) {
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

void print_all(List *list) {
  while (list) {
    list = print_ast(list, 0);
    printf("\n");
  }
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
#undef HANDLE
    return print_repeat(list, indent, 0);
  case AST_IDENTIFIER:
  case AST_FLOATING_CONSTANT:
  case AST_INTEGER_CONSTANT:
  case AST_ENUMERATION_CONSTANT:
  case AST_CHARACTER_CONSTANT:
  case AST_STRING_LITERAL:
    return print_token(list);
    /* Expressions */
  case AST_PRIMARY_EXPRESSION:
    return print_repeat(list, indent, 1);
  case AST_POSTFIX_EXPRESSION:
    list = print_tag(list);
    return print_repeat(list, indent, 2);
  case AST_UNARY_EXPRESSION:
    list = print_tag(list);
    return print_repeat(list, indent, 1);
  case AST_CAST_EXPRESSION:
    return print_repeat(list, indent, 2);
  case AST_BINARY:
    list = list_next(list);
    list = print_tag(list);
    return print_repeat(list, indent, 2);
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
    list = print_tag(list);
    return print_repeat(list, indent, 2);
  case AST_CONDITIONAL_EXPRESSION:
    return print_repeat(list, indent, 3);
  case AST_ASSIGNMENT_EXPRESSION:
    list = print_tag(list);
    return print_repeat(list, indent, 2);
  case AST_EXPRESSION:
    return print_repeat(list, indent, 2);
  case AST_CONSTANT_EXPRESSION:
    return print_repeat(list, indent, 1);
    /* Declarations */
  case AST_DECLARATION:
    return print_repeat(list, indent, 2);
  case AST_INIT_DECLARATOR:
    return print_repeat(list, indent, 2);
  case AST_STORAGE_CLASS_SPECIFIER:
    return print_repeat(list, indent, 1);
  case AST_TYPE_SPECIFIER:
    return print_repeat(list, indent, 1);
  case AST_STRUCT_OR_UNION_SPECIFIER:
    return print_repeat(list, indent, 3);
  case AST_STRUCT_DECLARATION:
    return print_repeat(list, indent, 2);
  case AST_STRUCT_DECLARATOR:
    return print_repeat(list, indent, 2);
  case AST_ENUM_SPECIFIER:
    return print_repeat(list, indent, 2);
  case AST_ENUMERATOR:
    return print_repeat(list, indent, 2);
  default:
    printf("[%s])", ast_show(list_tag(list)));
    return list_next(list);
  }
}
