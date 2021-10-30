#include "yyscan.h"

#include "parser.tab.h"
#include "util/util.h"

static yyscan_t yyscan_new(YYSCAN_EXTRA scanner) {
  yyscan_t self;
  if (yylex_init(&self) == 0) {
    yyset_extra(scanner, self);
    return self;
  }
  return NULL;
}
static void yyscan_delete(yyscan_t self) {
  if (self) {
    yylex_destroy(self);
  }
}

void yyerror(yyscan_t yyscanner, const char *msg) {
  UTIL_UNUSED(yyscanner);
  util_error("%s", msg);
}
void yyscan_parse(YYSCAN_EXTRA scanner) {
  yyscan_t self = yyscan_new(scanner);
  if (self) {
    yyparse(self);
  }
  yyscan_delete(self);
}
int yyscan_is_typedef(yyscan_t self, const char *symbol) {
  return scanner_is_typedef(yyget_extra(self), symbol);
}
void yyscan_register_typedef(yyscan_t self, YYSCAN_TYPE json) {
  if (scanner_contains_typedef(json)) {
    scanner_collect_typedef(yyget_extra(self), json);
  }
}
YYSCAN_TYPE yyscan_json_token(yyscan_t self) {
  const char *text = yyget_text(self);
  assert(text[yyget_leng(self)] == 0);
  return scanner_json_token(yyget_extra(self), text);
}
