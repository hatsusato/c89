#include "yyscan.h"

#include "json/json.h"
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
static void yyscan_del(yyscan_t self) {
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
  yyscan_del(self);
}
int yyscan_is_typedef(yyscan_t self, const char *symbol) {
  return scanner_is_typedef(yyget_extra(self), symbol);
}
YYSCAN_TYPE yyscan_json_token(yyscan_t self) {
  const char *text = yyget_text(self);
  assert(text[yyget_leng(self)] == 0);
  return scanner_json_token(yyget_extra(self), text);
}
YYSCAN_TYPE yyscan_json_null(void) {
  return json_null();
}
YYSCAN_TYPE yyscan_json_str(const char *str) {
  return json_new_str(str);
}
YYSCAN_TYPE yyscan_json_arr(void) {
  return json_new_arr();
}
YYSCAN_TYPE yyscan_json_obj(void) {
  return json_new_obj();
}
YYSCAN_TYPE yyscan_json_push(YYSCAN_TYPE arr, YYSCAN_TYPE val) {
  assert(json_is_arr(arr));
  json_arr_push(json_as_arr(arr), val);
  json_del(val);
  return arr;
}
YYSCAN_TYPE yyscan_json_insert(YYSCAN_TYPE obj, const char *key,
                               YYSCAN_TYPE val) {
  assert(json_is_obj(obj));
  json_obj_insert(json_as_obj(obj), key, val);
  json_del(val);
  return obj;
}
YYSCAN_TYPE yyscan_json_expr(const char *tag) {
  struct json *expr = yyscan_json_obj();
  yyscan_json_insert(expr, "tag", json_new_str(tag));
  return expr;
}
