#include "parser.h"

#include "string.h"

static YYSTYPE parser_new(int tag, void *data) {
  YYSTYPE ret = parser_init();
  ret.list = ret.last = list_new(tag, data);
  return ret;
}
static YYSTYPE parser_push(YYSTYPE x0, YYSTYPE x1) {
  assert(x0.list && x0.last);
  list_insert(x0.last, x1.list);
  x0.last = x1.last;
  return x0;
}
static YYSTYPE parser_push_tag(YYSTYPE x0, int tag) {
  return parser_push(x0, parser_new(tag, nil));
}
static YYSTYPE parser_arity(int arity, int tag) {
  YYSTYPE x0 = parser_new(arity, nil);
  x0 = parser_push_tag(x0, tag);
  return x0;
}
static void parser_list_closure(List *prev) {
  list_insert(list_next(prev), prev);
}
static YYSTYPE parser_list_last(YYSTYPE list) {
  YYSTYPE last = list;
  last.list = list.last;
  return last;
}

YYSTYPE parser_init(void) {
  YYSTYPE init = {nil, nil};
  return init;
}
YYSTYPE parser_token(int tag, yyscan_t scanner) {
  YYSTYPE ret = parser_new(AST_TOKEN, nil);
  String *str = string_new(yyget_text(scanner));
  ret = parser_push_tag(ret, tag);
  ret = parser_push(ret, parser_new(AST_DATA, str));
  return ret;
}
YYSTYPE parser_append0(int tag) {
  YYSTYPE x0 = parser_arity(AST_ARITY0, tag);
  return x0;
}
YYSTYPE parser_append1(int tag, YYSTYPE x1) {
  YYSTYPE x0 = parser_arity(AST_ARITY1, tag);
  x0 = parser_push(x0, x1);
  return x0;
}
YYSTYPE parser_append2(int tag, YYSTYPE x1, YYSTYPE x2) {
  YYSTYPE x0 = parser_arity(AST_ARITY2, tag);
  x0 = parser_push(x0, x1);
  x0 = parser_push(x0, x2);
  return x0;
}
YYSTYPE parser_append3(int tag, YYSTYPE x1, YYSTYPE x2, YYSTYPE x3) {
  YYSTYPE x0 = parser_arity(AST_ARITY3, tag);
  x0 = parser_push(x0, x1);
  x0 = parser_push(x0, x2);
  x0 = parser_push(x0, x3);
  return x0;
}
YYSTYPE parser_append4(int tag, YYSTYPE x1, YYSTYPE x2, YYSTYPE x3,
                       YYSTYPE x4) {
  YYSTYPE x0 = parser_arity(AST_ARITY4, tag);
  x0 = parser_push(x0, x1);
  x0 = parser_push(x0, x2);
  x0 = parser_push(x0, x3);
  x0 = parser_push(x0, x4);
  return x0;
}
YYSTYPE parser_binary(YYSTYPE x1, YYSTYPE x2, YYSTYPE x3) {
  return parser_append3(AST_BINARY, x2, x1, x3);
}
YYSTYPE parser_empty(void) {
  return parser_append0(AST_NIL);
}
YYSTYPE parser_list_empty(int tag) {
  YYSTYPE ret = parser_arity(AST_LIST, tag);
  List *prev = ret.last;
  ret = parser_push_tag(ret, AST_NIL);
  parser_list_closure(prev);
  return ret;
}
YYSTYPE parser_list_new(int tag, YYSTYPE elem) {
  return parser_list_push(parser_list_empty(tag), elem);
}
YYSTYPE parser_list_push(YYSTYPE list, YYSTYPE elem) {
  YYSTYPE last = parser_list_last(list);
  list.last = list_next(list.last);
  assert(list_next(list.last) == last.list);
  list = parser_push(list, elem);
  list = parser_push(list, last);
  parser_list_closure(elem.last);
  return list;
}
YYSTYPE parser_list_finish(YYSTYPE list) {
  parser_push(list, parser_init());
  return list;
}
