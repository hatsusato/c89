#include "parser.h"

#include "string.h"

static AstList parser_new(int tag, void *data) {
  AstList ret = parser_init();
  ret.list = ret.last = list_new(tag, data);
  return ret;
}
static AstList parser_push(AstList x0, AstList x1) {
  assert(x0.list && x0.last);
  list_insert(x0.last, x1.list);
  x0.last = x1.last;
  return x0;
}
static AstList parser_push_tag(AstList x0, int tag) {
  return parser_push(x0, parser_new(tag, nil));
}
static AstList parser_arity(int arity, int tag) {
  AstList x0 = parser_new(arity, nil);
  x0 = parser_push_tag(x0, tag);
  return x0;
}
static void parser_list_closure(List *prev) {
  list_insert(list_next(prev), prev);
}
static AstList parser_list_last(AstList list) {
  AstList last = list;
  last.list = list.last;
  return last;
}

AstList parser_init(void) {
  AstList init = {nil, nil};
  return init;
}
AstList parser_token(int tag, yyscan_t scanner) {
  AstList ret = parser_new(AST_TOKEN, nil);
  String *str = string_new(scanner_get_text(scanner));
  ret = parser_push_tag(ret, tag);
  ret = parser_push(ret, parser_new(AST_DATA, str));
  return ret;
}
AstList parser_append0(int tag) {
  AstList x0 = parser_arity(AST_ARITY0, tag);
  return x0;
}
AstList parser_append1(int tag, AstList x1) {
  AstList x0 = parser_arity(AST_ARITY1, tag);
  x0 = parser_push(x0, x1);
  return x0;
}
AstList parser_append2(int tag, AstList x1, AstList x2) {
  AstList x0 = parser_arity(AST_ARITY2, tag);
  x0 = parser_push(x0, x1);
  x0 = parser_push(x0, x2);
  return x0;
}
AstList parser_append3(int tag, AstList x1, AstList x2, AstList x3) {
  AstList x0 = parser_arity(AST_ARITY3, tag);
  x0 = parser_push(x0, x1);
  x0 = parser_push(x0, x2);
  x0 = parser_push(x0, x3);
  return x0;
}
AstList parser_append4(int tag, AstList x1, AstList x2, AstList x3,
                       AstList x4) {
  AstList x0 = parser_arity(AST_ARITY4, tag);
  x0 = parser_push(x0, x1);
  x0 = parser_push(x0, x2);
  x0 = parser_push(x0, x3);
  x0 = parser_push(x0, x4);
  return x0;
}
AstList parser_binary(AstList x1, AstList x2, AstList x3) {
  return parser_append3(AST_BINARY, x2, x1, x3);
}
AstList parser_empty(void) {
  return parser_append0(AST_NIL);
}
AstList parser_list_empty(int tag) {
  AstList ret = parser_arity(AST_LIST, tag);
  List *prev = ret.last;
  ret = parser_push_tag(ret, AST_NIL);
  parser_list_closure(prev);
  return ret;
}
AstList parser_list_new(int tag, AstList elem) {
  return parser_list_push(parser_list_empty(tag), elem);
}
AstList parser_list_push(AstList list, AstList elem) {
  AstList last = parser_list_last(list);
  list.last = list_next(list.last);
  assert(list_next(list.last) == last.list);
  list = parser_push(list, elem);
  list = parser_push(list, last);
  parser_list_closure(elem.last);
  return list;
}
AstList parser_list_finish(AstList list) {
  parser_push(list, parser_init());
  return list;
}
List *parser_consume(List *ast) {
  int tag = list_tag(ast);
  ast = list_next(ast);
  ast = list_next(ast);
  switch (tag) {
  case AST_TOKEN:
    return list_next(ast);
  case AST_LIST:
    while (AST_NIL != list_tag(ast)) {
      ast = parser_consume(ast);
    }
    return list_next(ast);
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
    ast = parser_consume(ast);
  case_arity3:
    ast = parser_consume(ast);
  case_arity2:
    ast = parser_consume(ast);
  case_arity1:
    ast = parser_consume(ast);
  case_arity0:
    return ast;
  default:
    assert(0);
    return ast;
  }
}
