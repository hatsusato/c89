#include "pretty.h"

#include <assert.h>
#include <stdio.h>

#include "ast.h"
#include "print.h"

static List *pretty_token(List *ast, int indent) {
  (void)indent;
  ast = list_next(ast);
  return print_data(ast);
}
static List *pretty_list(List *ast, int indent) {
  const char *delims[] = {"", "", ""};
  int indents[] = {0, 0};
  switch (list_tag(ast)) {
  case AST_DECLARATION_SPECIFIERS:
  case AST_SPECIFIER_QUALIFIER_LIST:
  case AST_TYPE_QUALIFIER_LIST:
  case AST_ARGUMENT_EXPRESSION_LIST:
  case AST_INIT_DECLARATOR_LIST:
  case AST_STRUCT_DECLARATOR_LIST:
  case AST_ENUMERATOR_LIST:
  case AST_PARAMETER_LIST:
  case AST_IDENTIFIER_LIST:
  case AST_INITIALIZER_LIST:
  case AST_STRUCT_DECLARATION_LIST:
  case AST_DECLARATION_LIST:
  case AST_STATEMENT_LIST:
  case AST_TRANSLATION_UNIT:
    break;
  default:
    assert(0);
  }
  ast = list_next(ast);
  printf("%s", delims[0]);
  if (AST_NIL != list_tag(ast)) {
    ast = pretty_print(ast, indents[0]);
  }
  while (AST_NIL != list_tag(ast)) {
    printf("%s", delims[1]);
    ast = pretty_print(ast, indents[1]);
  }
  printf("%s", delims[2]);
  return list_next(ast);
}
static List *pretty_binary(List *ast, int indent) {
  int op = 0;
  assert(AST_ARITY0 == list_tag(ast));
  ast = list_next(ast);
  op = list_tag(ast);
  ast = list_next(ast);
  ast = pretty_print(ast, indent);
  printf(" %s ", ast_show(op));
  ast = pretty_print(ast, indent);
  return ast;
}
static List *pretty_arity0(List *ast, int indent) {
  (void)indent;
  printf("%s", ast_show(list_tag(ast)));
  return list_next(ast);
}
static List *pretty_arity1(List *ast, int indent) {
  const char *delims[] = {"", ""};
  switch (list_tag(ast)) {
  case AST_PRIMARY_EXPRESSION:
  case AST_CALL:
  case AST_UNARY_EXPRESSION:
  case AST_CONSTANT_EXPRESSION:
  case AST_OLD:
  case AST_POINTER:
  case AST_PARAMETER_DECLARATION:
  case AST_TYPE_NAME:
  case AST_ABSTRACT_DECLARATOR:
  case AST_DIRECT_ABSTRACT_DECLARATOR:
  case AST_TYPEDEF_NAME:
  case AST_STATEMENT:
  case AST_SELECTION_STATEMENT:
  case AST_ITERATION_STATEMENT:
  case AST_EXTERNAL_DECLARATION:
  case AST_FUNCTION_DEFINITION:
  case AST_ARRAY:
  case AST_PERIOD:
  case AST_ARROW:
  case AST_SIZEOF:
  case AST_DECLARATION:
  case AST_EXPRESSION_STATEMENT:
  case AST_JUMP_STATEMENT:
  case AST_INIT_DECLARATOR:
  case AST_STORAGE_CLASS_SPECIFIER:
  case AST_TYPE_SPECIFIER:
  case AST_STRUCT_DECLARATOR:
  case AST_ENUMERATOR:
  case AST_TYPE_QUALIFIER:
  case AST_DECLARATOR:
  case AST_DIRECT_DECLARATOR:
  case AST_ENUM_SPECIFIER:
  case AST_PARAMETER_TYPE_LIST:
  case AST_INITIALIZER:
  case AST_CASE:
  case AST_GOTO:
  case AST_RETURN:
    break;
  default:
    assert(0);
  }
  ast = list_next(ast);
  printf("%s", delims[0]);
  ast = pretty_print(ast, indent);
  printf("%s", delims[1]);
  return ast;
}
static List *pretty_arity2(List *ast, int indent) {
  const char *delims[] = {"", "", ""};
  int indents[] = {0, 0};
  switch (list_tag(ast)) {
  case AST_POSTFIX_EXPRESSION:
  case AST_UNARY_EXPRESSION:
  case AST_CAST_EXPRESSION:
  case AST_DECLARATION:
  case AST_STRUCT_DECLARATION:
  case AST_INIT_DECLARATOR:
  case AST_STRUCT_OR_UNION_SPECIFIER:
  case AST_DECLARATOR:
  case AST_DIRECT_DECLARATOR:
  case AST_POINTER:
  case AST_PARAMETER_DECLARATION:
  case AST_TYPE_NAME:
  case AST_ABSTRACT_DECLARATOR:
  case AST_DIRECT_ABSTRACT_DECLARATOR:
  case AST_OLD:
  case AST_STRUCT_DECLARATOR:
  case AST_ENUM_SPECIFIER:
  case AST_ENUMERATOR:
  case AST_LABELED_STATEMENT:
  case AST_COMPOUND_STATEMENT:
  case AST_IF:
  case AST_SWITCH:
  case AST_WHILE:
  case AST_DO:
    break;
  default:
    assert(0);
  }
  ast = list_next(ast);
  printf("%s", delims[0]);
  ast = pretty_print(ast, indents[0]);
  printf("%s", delims[1]);
  ast = pretty_print(ast, indents[1]);
  printf("%s", delims[2]);
  return ast;
}
static List *pretty_arity3(List *ast, int indent) {
  const char *delims[] = {"", "", "", ""};
  int indents[] = {0, 0, 0};
  switch (list_tag(ast)) {
  case AST_BINARY:
    return pretty_binary(list_next(ast), indent);
  case AST_CONDITIONAL_EXPRESSION:
  case AST_STRUCT_OR_UNION_SPECIFIER:
  case AST_IF:
  case AST_FUNCTION_DEFINITION:
  case AST_OLD:
    break;
  default:
    assert(0);
  }
  ast = list_next(ast);
  printf("%s", delims[0]);
  ast = pretty_print(ast, indents[0]);
  printf("%s", delims[1]);
  ast = pretty_print(ast, indents[1]);
  printf("%s", delims[2]);
  ast = pretty_print(ast, indents[2]);
  printf("%s", delims[3]);
  return ast;
}
static List *pretty_arity4(List *ast, int indent) {
  const char *delims[] = {"", "", "", ""};
  int indents[] = {0, 0, 0, 0};
  switch (list_tag(ast)) {
  case AST_FOR:
  case AST_OLD:
    break;
  default:
    assert(0);
  }
  ast = list_next(ast);
  printf("%s", delims[0]);
  ast = pretty_print(ast, indents[0]);
  printf("%s", delims[1]);
  ast = pretty_print(ast, indents[1]);
  printf("%s", delims[2]);
  ast = pretty_print(ast, indents[2]);
  printf("%s", delims[3]);
  ast = pretty_print(ast, indents[3]);
  return ast;
}

List *pretty_print(List *ast, int indent) {
  int tag = list_tag(ast);
  ast = list_next(ast);
  switch (tag) {
  case AST_TOKEN:
    return pretty_token(ast, indent);
  case AST_LIST:
    return pretty_list(ast, indent);
  case AST_ARITY0:
    return pretty_arity0(ast, indent);
  case AST_ARITY1:
    return pretty_arity1(ast, indent);
  case AST_ARITY2:
    return pretty_arity2(ast, indent);
  case AST_ARITY3:
    return pretty_arity3(ast, indent);
  case AST_ARITY4:
    return pretty_arity4(ast, indent);
  default:
    assert(0);
  }
  return ast;
}
