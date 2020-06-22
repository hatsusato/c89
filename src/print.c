#include "print.h"

#include <ctype.h>
#include <stdio.h>

#include "ast.h"
#include "vector.h"

static void print_indent(int indent) {
  for (; 0 < indent; --indent) {
    printf("  ");
  }
}
static void print_begin(int indent) {
  printf("\n");
  print_indent(indent);
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
  print_data(list_data(list));
  return list_next(list);
}
static List *print_list(List *list, int indent) {
  while (AST_NIL != list_tag(list)) {
    list = print_ast(list, indent);
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

static List *print_consume(List *ast) {
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
static List *print_pretty_list(List *ast, int indent) {
  const char *delim = "";
  switch (list_tag(ast)) {
  case AST_DECLARATION_SPECIFIERS:
  case AST_SPECIFIER_QUALIFIER_LIST:
  case AST_TYPE_QUALIFIER_LIST:
    delim = " ";
    break;
  case AST_ARGUMENT_EXPRESSION_LIST:
  case AST_INIT_DECLARATOR_LIST:
  case AST_STRUCT_DECLARATOR_LIST:
  case AST_ENUMERATOR_LIST:
  case AST_PARAMETER_LIST:
  case AST_IDENTIFIER_LIST:
  case AST_INITIALIZER_LIST:
    delim = ", ";
    break;
  case AST_STRUCT_DECLARATION_LIST:
  case AST_DECLARATION_LIST:
  case AST_STATEMENT_LIST:
  case AST_TRANSLATION_UNIT:
    delim = "\n";
    break;
  default:
    assert(0);
  }
  ast = list_next(ast);
  if (AST_NIL != list_tag(ast)) {
    ast = print_pretty(ast, indent);
  }
  while (AST_NIL != list_tag(ast)) {
    printf("%s", delim);
    ast = print_pretty(ast, indent);
  }
  return list_next(ast);
}
static List *print_pretty_binary(List *ast, int indent) {
  int op = 0;
  assert(AST_ARITY0 == list_tag(ast));
  ast = list_next(ast);
  op = list_tag(ast);
  ast = list_next(ast);
  printf("(");
  ast = print_pretty(ast, indent);
  printf(" %s ", ast_show(op));
  ast = print_pretty(ast, indent);
  printf(")");
  return ast;
}
static List *print_pretty_arity0(List *ast, int indent) {
  printf("%s", ast_show(list_tag(ast)));
  return list_next(ast);
}
static List *print_pretty_arity4(List *ast, int indent) {
  const char *delims[] = {"", "", "", ""};
  switch (list_tag(ast)) {
  case AST_FOR:
    delims[0] = "(";
    delims[1] = "; ";
    delims[2] = "; ";
    delims[3] = ")";
    break;
  case AST_OLD:
    delims[1] = " ";
    delims[2] = " ";
    delims[3] = " ";
    break;
  default:
    assert(0);
  }
  ast = list_next(ast);
  printf("%s", delims[0]);
  ast = print_pretty(ast, indent);
  printf("%s", delims[1]);
  ast = print_pretty(ast, indent);
  printf("%s", delims[2]);
  ast = print_pretty(ast, indent);
  printf("%s", delims[3]);
  ast = print_pretty(ast, indent);
  return ast;
}

List *print_pretty(List *ast, int indent) {
  switch (list_tag(ast)) {
  case AST_TOKEN:
    ast = list_next(ast);
    ast = list_next(ast);
    return print_token(ast);
  case AST_LIST:
    ast = list_next(ast);
    return print_pretty_list(ast, indent);
  case AST_ARITY0:
    ast = list_next(ast);
    return print_pretty_arity0(ast, indent);
  case AST_ARITY1:
    ast = list_next(ast);
    ast = list_next(ast);
    return print_pretty(ast, indent);
  case AST_ARITY2:
    ast = list_next(ast);
    ast = list_next(ast);
    ast = print_pretty(ast, indent);
    return print_pretty(ast, indent);
  case AST_ARITY3:
    ast = list_next(ast);
    ast = list_next(ast);
    ast = print_pretty(ast, indent);
    ast = print_pretty(ast, indent);
    return print_pretty(ast, indent);
  case AST_ARITY4:
    ast = list_next(ast);
    return print_pretty_arity4(ast, indent);
  default:
    assert(0);
  }
  return ast;
}
