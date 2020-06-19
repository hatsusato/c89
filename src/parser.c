#include "parser.h"

YYSTYPE ast_init(void) {
  YYSTYPE init = {nil, nil};
  return init;
}
void yyerror(const char *msg, yyscan_t scanner) {
  (void)scanner;
  fprintf(stderr, "yyerror: [%s]\n", msg);
}
YYSTYPE ast_new_token(int tag, yyscan_t scanner) {
  YYSTYPE ret = ast_init();
  const char *text = yyget_text(scanner);
  int leng = yyget_leng(scanner);
  Vector *vec = vector_new(1);
  vector_append(vec, text, leng);
  ret.list = list_new(tag, vec);
  return ret;
}
YYSTYPE ast_new_tag(int tag) {
  YYSTYPE ret = ast_init();
  ret.list = list_new(tag, nil);
  return ret;
}
YYSTYPE ast_append1(int tag, YYSTYPE x1) {
  YYSTYPE x0 = ast_arity1(tag);
  x0 = ast_push(x0, x1);
  return x0;
}
YYSTYPE ast_append2(int tag, YYSTYPE x1, YYSTYPE x2) {
  YYSTYPE x0 = ast_arity2(tag);
  x0 = ast_push(x0, x1);
  x0 = ast_push(x0, x2);
  return x0;
}
YYSTYPE ast_append3(int tag, YYSTYPE x1, YYSTYPE x2, YYSTYPE x3) {
  YYSTYPE x0 = ast_arity3(tag);
  x0 = ast_push(x0, x1);
  x0 = ast_push(x0, x2);
  x0 = ast_push(x0, x3);
  return x0;
}
YYSTYPE ast_push(YYSTYPE x0, YYSTYPE x1) {
  x0.list = list_append(x0.list, x1.list);
  return x0;
}
YYSTYPE ast_push_tag(YYSTYPE x0, int tag) {
  return ast_push(x0, ast_new_tag(tag));
}
static YYSTYPE ast_arity_aux(int arity, int tag) {
  return ast_push_tag(ast_new_tag(arity), tag);
}
YYSTYPE ast_arity0(int tag) {
  return ast_arity_aux(AST_ARITY0, tag);
}
YYSTYPE ast_arity1(int tag) {
  return ast_arity_aux(AST_ARITY1, tag);
}
YYSTYPE ast_arity2(int tag) {
  return ast_arity_aux(AST_ARITY2, tag);
}
YYSTYPE ast_arity3(int tag) {
  return ast_arity_aux(AST_ARITY3, tag);
}
YYSTYPE ast_binary(YYSTYPE x1, YYSTYPE x2, YYSTYPE x3) {
  return ast_append3(AST_BINARY, x2, x1, x3);
}
