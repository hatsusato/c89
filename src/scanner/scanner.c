#include "scanner.h"

#include "json/factory.h"
#include "json/json.h"
#include "set/set.h"
#include "type.h"
#include "util/util.h"

YYSCAN_EXTRA scanner_new(struct json_factory *factory, struct set *symbols) {
  YYSCAN_EXTRA self = util_malloc(sizeof(struct scanner));
  self->typedefs = set_new();
  self->symbols = symbols;
  self->jfactory = factory;
  self->top = json_null();
  return self;
}
void scanner_delete(YYSCAN_EXTRA self) {
  set_delete(self->typedefs);
  util_free(self);
}
YYSCAN_TYPE scanner_json_token(YYSCAN_EXTRA self, const char *token) {
  token = set_insert(self->symbols, token);
  return json_factory_str(self->jfactory, token);
}
YYSCAN_TYPE scanner_json_str(YYSCAN_EXTRA self, const char *symbol) {
  return json_factory_str(self->jfactory, symbol);
}
YYSCAN_TYPE scanner_json_arr(YYSCAN_EXTRA self) {
  return json_factory_arr(self->jfactory);
}
YYSCAN_TYPE scanner_json_obj(YYSCAN_EXTRA self) {
  return json_factory_obj(self->jfactory);
}
YYSCAN_TYPE scanner_json_push(YYSCAN_TYPE arr, YYSCAN_TYPE val) {
  json_arr_push(arr, val);
  return arr;
}
void scanner_json_set(YYSCAN_TYPE self, const char *key, YYSCAN_TYPE val) {
  json_obj_set(self, key, val);
}
void scanner_set_top(YYSCAN_EXTRA self, YYSCAN_TYPE top) {
  self->top = top;
}
