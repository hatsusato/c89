#include "yyscan.h"

#include "parser.tab.h"
#include "util/util.h"

void yyerror(yyscan_t yyscanner, const char *msg) {
  UTIL_UNUSED(yyscanner);
  util_error("%s", msg);
}
yyscan_t yyscan_new(YYSCAN_EXTRA scanner) {
  yyscan_t self;
  if (yylex_init(&self) == 0) {
    yyset_extra(scanner, self);
    return self;
  }
  return NULL;
}
void yyscan_delete(yyscan_t self) {
  if (self) {
    yylex_destroy(self);
  }
}
void yyscan_parse(yyscan_t self) {
  yyparse(self);
}
int yyscan_is_typedef(yyscan_t self, const char *symbol) {
  return scanner_is_typedef(yyget_extra(self), symbol);
}
YYSCAN_TYPE yyscan_json_token(yyscan_t self) {
  const char *text = yyget_text(self);
  assert(text[yyget_leng(self)] == 0);
  return scanner_json_token(yyget_extra(self), text);
}
