#include "parser.h"

static YYSTYPE yystype_init(void) {
  YYSTYPE init = {nil, nil};
  return init;
}
void yyerror(const char *msg, yyscan_t scanner) {
  (void)scanner;
  fprintf(stderr, "yyerror: [%s]\n", msg);
}
YYSTYPE ast_new_token(int tag, yyscan_t scanner) {
  YYSTYPE ret = yystype_init();
  const char *text = yyget_text(scanner);
  int leng = yyget_leng(scanner);
  Vector *vec = vector_new(1);
  vector_append(vec, text, leng);
  ret.list = list_new(tag, vec);
  return ret;
}
YYSTYPE ast_new_tag(int tag) {
  YYSTYPE ret = yystype_init();
  ret.list = list_new(tag, nil);
  return ret;
}
