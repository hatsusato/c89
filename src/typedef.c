#include "typedef.h"

#include "list.h"
#include "parser.h"
#include "scanner.h"
#include "string.h"
#include "utility.h"

static List *typedef_parse_declarator(yyscan_t, List *);
static List *typedef_insert(yyscan_t scanner, List *ast) {
  assert(AST_DATA == list_tag(ast));
  scanner_insert_symbol(scanner, string_begin(list_data(ast)));
  return list_next(ast);
}
static List *typedef_next(List *ast, int tag) {
  assert(tag == list_tag(ast));
  return list_next(ast);
}
static List *typedef_parse_direct_declarator(yyscan_t scanner, List *ast) {
  int tag = list_tag(ast);
  ast = list_next(ast);
  switch (tag) {
  case AST_TOKEN:
    ast = typedef_next(ast, AST_IDENTIFIER);
    return typedef_insert(scanner, ast);
  case AST_ARITY1:
    ast = typedef_next(ast, AST_DIRECT_DECLARATOR);
    return typedef_parse_declarator(scanner, ast);
  case AST_ARITY2:
    ast = typedef_next(ast, AST_DIRECT_DECLARATOR);
    ast = typedef_parse_direct_declarator(scanner, ast);
    return parser_consume(ast);
  default:
    assert(0);
    return ast;
  }
}
static List *typedef_parse_declarator(yyscan_t scanner, List *ast) {
  int tag = list_tag(ast);
  ast = list_next(ast);
  switch (tag) {
  case AST_ARITY1:
    ast = typedef_next(ast, AST_DECLARATOR);
    return typedef_parse_direct_declarator(scanner, ast);
  case AST_ARITY2:
    ast = typedef_next(ast, AST_DECLARATOR);
    ast = parser_consume(ast);
    return typedef_parse_direct_declarator(scanner, ast);
  default:
    assert(0);
    return ast;
  }
}
static List *typedef_parse_init_declarator(yyscan_t scanner, List *ast) {
  int tag = list_tag(ast);
  ast = list_next(ast);
  switch (tag) {
  case AST_ARITY1:
    ast = typedef_next(ast, AST_INIT_DECLARATOR);
    return typedef_parse_declarator(scanner, ast);
  case AST_ARITY2:
    ast = typedef_next(ast, AST_INIT_DECLARATOR);
    ast = typedef_parse_declarator(scanner, ast);
    return parser_consume(ast);
  default:
    assert(0);
    return ast;
  }
}
static Bool typedef_in_range(AstList ast) {
  List *list = ast.list;
  while (list != ast.last) {
    if (AST_TYPEDEF == list_tag(list)) {
      return true;
    }
    list = list_next(list);
  }
  return false;
}
