#include "yyscan.h"

#include "json/factory.h"
#include "json/json.h"
#include "parser.tab.h"
#include "set/set.h"
#include "type.h"
#include "typedef.h"
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
  const char *found = set_find(yyget_extra(self)->typedefs, symbol);
  return found ? 1 : 0;
}

YYSCAN_TYPE yyscan_json_token(yyscan_t self) {
  const char *text = yyget_text(self);
  assert(text[yyget_leng(self)] == 0);
  return yyscan_json_symbol(self, text);
}
YYSCAN_TYPE yyscan_json_symbol(yyscan_t self, const char *symbol) {
  symbol = set_insert(yyget_extra(self)->symbols, symbol);
  return json_factory_str(yyget_extra(self)->jfactory, symbol);
}
YYSCAN_TYPE yyscan_json_arr(yyscan_t self) {
  return json_factory_arr(yyget_extra(self)->jfactory);
}
YYSCAN_TYPE yyscan_json_push(YYSCAN_TYPE json, YYSCAN_TYPE val) {
  json_arr_push(json, val);
  return json;
}
YYSCAN_TYPE yyscan_json_obj(yyscan_t self) {
  return json_factory_obj(yyget_extra(self)->jfactory);
}
void yyscan_json_insert(YYSCAN_TYPE json, const char *key, YYSCAN_TYPE val) {
  json_obj_set(json, key, val);
}
void yyscan_set_top(yyscan_t self, YYSCAN_TYPE top) {
  yyget_extra(self)->top = top;
}
