#include "parser.h"

void yyerror(const char *msg, yyscan_t scanner) {
  (void)scanner;
  fprintf(stderr, "yyerror: [%s]\n", msg);
}
List *ast_new_token(int tag, yyscan_t scanner) {
  const char *text = yyget_text(scanner);
  int leng = yyget_leng(scanner);
  Vector *vec = vector_new(1);
  vector_append(vec, text, leng);
  return list_new(tag, vec);
}
List *ast_new_tag(int tag) {
  return list_new(tag, nil);
}
