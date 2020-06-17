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
YYSTYPE ast_list_append(YYSTYPE lhs, YYSTYPE rhs) {
  lhs.list = list_append(lhs.list, rhs.list);
  return lhs;
}
YYSTYPE ast_append1(int tag, YYSTYPE x1) {
  YYSTYPE x0 = ast_new_tag(AST_ARITY1);
  x0 = ast_list_append(x0, ast_new_tag(tag));
  x0 = ast_list_append(x0, x1);
  return x0;
}
