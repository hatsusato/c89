#include "pretty.h"

#include <assert.h>
#include <stdio.h>

#include "ast.h"
#include "print.h"

static List *print_pretty_token(List *ast, int indent) {
  (void)indent;
  ast = list_next(ast);
  return print_data(ast);
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
  (void)indent;
  printf("%s", ast_show(list_tag(ast)));
  return list_next(ast);
}
static List *print_pretty_arity1(List *ast, int indent) {
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
    delims[0] = "(";
    delims[1] = ")";
    break;
  case AST_ARRAY:
    delims[0] = "[";
    delims[1] = "]";
    break;
  case AST_PERIOD:
    delims[0] = ".";
    break;
  case AST_ARROW:
    delims[0] = "->";
    break;
  case AST_SIZEOF:
    delims[0] = "sizeof(";
    delims[1] = ")";
    break;
  case AST_DECLARATION:
  case AST_EXPRESSION_STATEMENT:
  case AST_JUMP_STATEMENT:
    delims[0] = ";\n";
    break;
  case AST_INIT_DECLARATOR:
  case AST_STORAGE_CLASS_SPECIFIER:
  case AST_TYPE_SPECIFIER:
  case AST_STRUCT_DECLARATOR:
  case AST_ENUMERATOR:
  case AST_TYPE_QUALIFIER:
  case AST_DECLARATOR:
  case AST_DIRECT_DECLARATOR:
    break;
  case AST_ENUM_SPECIFIER:
    delims[0] = "enum ";
    break;
  case AST_PARAMETER_TYPE_LIST:
    delims[0] = ", ...";
    break;
  case AST_INITIALIZER:
    delims[0] = "{";
    delims[1] = "}";
    break;
  case AST_CASE:
    delims[0] = "case ";
    break;
  case AST_GOTO:
    delims[0] = "goto ";
    delims[1] = ";\n";
    break;
  case AST_RETURN:
    delims[0] = "return ";
    delims[1] = ";\n";
    break;
  default:
    assert(0);
  }
  ast = list_next(ast);
  printf("%s", delims[0]);
  ast = print_pretty(ast, indent);
  printf("%s", delims[1]);
  return ast;
}
static List *print_pretty_arity2(List *ast, int indent) {
  const char *delims[] = {"", "", ""};
  switch (list_tag(ast)) {
  case AST_POSTFIX_EXPRESSION:
  case AST_UNARY_EXPRESSION:
    delims[0] = "(";
    delims[2] = ")";
    break;
  case AST_CAST_EXPRESSION:
    delims[0] = "((";
    delims[1] = ")";
    delims[2] = ")";
    break;
  case AST_DECLARATION:
  case AST_STRUCT_DECLARATION:
    delims[1] = " ";
    delims[2] = ";";
    break;
  case AST_INIT_DECLARATOR:
    delims[1] = " = ";
    delims[2] = ";";
    break;
  case AST_STRUCT_OR_UNION_SPECIFIER:
  case AST_DECLARATOR:
  case AST_DIRECT_DECLARATOR:
  case AST_POINTER:
  case AST_PARAMETER_DECLARATION:
  case AST_TYPE_NAME:
  case AST_ABSTRACT_DECLARATOR:
  case AST_DIRECT_ABSTRACT_DECLARATOR:
  case AST_OLD:
    delims[1] = " ";
    break;
  case AST_STRUCT_DECLARATOR:
    delims[1] = " : ";
    break;
  case AST_ENUM_SPECIFIER:
    delims[0] = "enum ";
    delims[1] = " {\n";
    delims[2] = "\n}";
    break;
  case AST_ENUMERATOR:
    delims[1] = " = ";
    break;
  case AST_LABELED_STATEMENT:
    delims[1] = ":";
    delims[2] = "\n";
    break;
  case AST_COMPOUND_STATEMENT:
    delims[0] = "{\n";
    delims[2] = "\n}";
    break;
  case AST_IF:
  case AST_SWITCH:
  case AST_WHILE:
    delims[0] = "(";
    delims[1] = ")";
    break;
  case AST_DO:
    delims[1] = "while (";
    delims[2] = ");";
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
  return ast;
}
static List *print_pretty_arity3(List *ast, int indent) {
  const char *delims[] = {"", "", "", ""};
  switch (list_tag(ast)) {
  case AST_BINARY:
    return print_pretty_binary(list_next(ast), indent);
  case AST_CONDITIONAL_EXPRESSION:
    delims[0] = "(";
    delims[1] = " ? ";
    delims[2] = " : ";
    delims[3] = ")";
    break;
  case AST_STRUCT_OR_UNION_SPECIFIER:
    delims[1] = " ";
    delims[2] = " {\n";
    delims[3] = "\n}";
    break;
  case AST_IF:
    delims[0] = "(";
    delims[1] = ") ";
    delims[2] = " else ";
    break;
  case AST_FUNCTION_DEFINITION:
  case AST_OLD:
    delims[1] = " ";
    delims[2] = " ";
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
  return ast;
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
  int tag = list_tag(ast);
  ast = list_next(ast);
  switch (tag) {
  case AST_TOKEN:
    return print_pretty_token(ast, indent);
  case AST_LIST:
    return print_pretty_list(ast, indent);
  case AST_ARITY0:
    return print_pretty_arity0(ast, indent);
  case AST_ARITY1:
    return print_pretty_arity1(ast, indent);
  case AST_ARITY2:
    return print_pretty_arity2(ast, indent);
  case AST_ARITY3:
    return print_pretty_arity3(ast, indent);
  case AST_ARITY4:
    return print_pretty_arity4(ast, indent);
  default:
    assert(0);
  }
  return ast;
}
