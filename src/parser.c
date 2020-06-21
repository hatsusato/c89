#include "parser.h"

#include "vector.h"

static YYSTYPE ast_new(int tag, void *data) {
  YYSTYPE ret = ast_init();
  ret.list = ret.last = list_new(tag, data);
  return ret;
}
static YYSTYPE ast_push(YYSTYPE x0, YYSTYPE x1) {
  if (x0.last) {
    list_insert(x0.last, x1.list);
    x0.last = x1.last;
  } else {
    x0 = x1;
  }
  return x0;
}
static YYSTYPE ast_push_tag(YYSTYPE x0, int tag) {
  return ast_push(x0, ast_new_tag(tag));
}
static YYSTYPE ast_arity(int arity, int tag) {
  YYSTYPE x0 = ast_new_tag(arity);
  x0 = ast_push_tag(x0, tag);
  return x0;
}

void yyerror(const char *msg, yyscan_t scanner) {
  (void)scanner;
  fprintf(stderr, "yyerror: [%s]\n", msg);
}
YYSTYPE ast_init(void) {
  YYSTYPE init = {nil, nil};
  return init;
}
YYSTYPE ast_new_token(int tag, yyscan_t scanner) {
  const char *text = yyget_text(scanner);
  int leng = yyget_leng(scanner);
  Vector *vec = vector_new(1);
  vector_append(vec, text, leng);
  return ast_new(tag, vec);
}
YYSTYPE ast_new_tag(int tag) {
  return ast_new(tag, nil);
}
YYSTYPE ast_append0(int tag) {
  YYSTYPE x0 = ast_arity(AST_ARITY0, tag);
  return x0;
}
YYSTYPE ast_append1(int tag, YYSTYPE x1) {
  YYSTYPE x0 = ast_arity(AST_ARITY1, tag);
  x0 = ast_push(x0, x1);
  return x0;
}
YYSTYPE ast_append2(int tag, YYSTYPE x1, YYSTYPE x2) {
  YYSTYPE x0 = ast_arity(AST_ARITY2, tag);
  x0 = ast_push(x0, x1);
  x0 = ast_push(x0, x2);
  return x0;
}
YYSTYPE ast_append3(int tag, YYSTYPE x1, YYSTYPE x2, YYSTYPE x3) {
  YYSTYPE x0 = ast_arity(AST_ARITY3, tag);
  x0 = ast_push(x0, x1);
  x0 = ast_push(x0, x2);
  x0 = ast_push(x0, x3);
  return x0;
}
YYSTYPE ast_append4(int tag, YYSTYPE x1, YYSTYPE x2, YYSTYPE x3, YYSTYPE x4) {
  YYSTYPE x0 = ast_arity(AST_ARITY4, tag);
  x0 = ast_push(x0, x1);
  x0 = ast_push(x0, x2);
  x0 = ast_push(x0, x3);
  x0 = ast_push(x0, x4);
  return x0;
}
YYSTYPE ast_binary(YYSTYPE x1, YYSTYPE x2, YYSTYPE x3) {
  return ast_append3(AST_BINARY, x2, x1, x3);
}
YYSTYPE ast_list_empty(int tag) {
  YYSTYPE ret = ast_push_tag(ast_new_tag(AST_LIST), tag);
  List *prev = ret.last;
  ret = ast_push_tag(ret, AST_NIL);
  list_insert(ret.last, prev);
  return ret;
}
YYSTYPE ast_list_new(int tag, YYSTYPE elem) {
  return ast_list_push(ast_list_empty(tag), elem);
}
YYSTYPE ast_list_push(YYSTYPE list, YYSTYPE elem) {
  assert(list_next(last) == list.last);
  list_insert(list_next(list.last), elem.list);
  list_insert(elem.last, list.last);
  list_insert(list.last, elem.last);
  return list;
}
void ast_list_finish(YYSTYPE list) {
  list_insert(list.last, nil);
}
