#include "scanner.h"

#include "json/factory.h"
#include "json/json.h"
#include "json/visitor.h"
#include "set/set.h"
#include "symbol.h"
#include "util/util.h"

struct scanner {
  struct json_factory *factory;
  YYSCAN_TYPE top;
  struct set *tokens, *typedefs;
};

YYSCAN_EXTRA scanner_new(struct json_factory *factory, struct set *symbols) {
  YYSCAN_EXTRA self = util_malloc(sizeof(struct scanner));
  self->factory = factory;
  self->top = json_null();
  self->typedefs = set_new();
  self->tokens = symbols;
  return self;
}
void scanner_delete(YYSCAN_EXTRA self) {
  set_delete(self->typedefs);
  util_free(self);
}
YYSCAN_TYPE scanner_json_token(YYSCAN_EXTRA self, const char *token) {
  token = set_insert(self->tokens, token);
  return json_factory_str(self->factory, token);
}
YYSCAN_TYPE scanner_json_str(YYSCAN_EXTRA self, const char *symbol) {
  return json_factory_str(self->factory, symbol);
}
YYSCAN_TYPE scanner_json_arr(YYSCAN_EXTRA self) {
  return json_factory_arr(self->factory);
}
YYSCAN_TYPE scanner_json_obj(YYSCAN_EXTRA self) {
  return json_factory_obj(self->factory);
}
YYSCAN_TYPE scanner_json_push(YYSCAN_TYPE arr, YYSCAN_TYPE val) {
  struct json_arr *jarr = json_as_arr(arr);
  assert(jarr);
  json_arr_push(jarr, val);
  return arr;
}
YYSCAN_TYPE scanner_json_set(YYSCAN_TYPE obj, const char *key,
                             YYSCAN_TYPE val) {
  json_json_obj_set(obj, key, val);
  return obj;
}
YYSCAN_TYPE scanner_json_binop(YYSCAN_EXTRA self, YYSCAN_TYPE lhs,
                               YYSCAN_TYPE op, YYSCAN_TYPE rhs) {
  YYSCAN_TYPE expr = scanner_json_obj(self);
  scanner_json_set(expr, "lhs", lhs);
  scanner_json_set(expr, "op", op);
  scanner_json_set(expr, "rhs", rhs);
  return expr;
}
YYSCAN_TYPE scanner_get_top(YYSCAN_EXTRA self) {
  return self->top;
}
void scanner_set_top(YYSCAN_EXTRA self, YYSCAN_TYPE top) {
  self->top = top;
}
int scanner_is_typedef(YYSCAN_EXTRA self, const char *symbol) {
  const char *found = set_find(self->typedefs, symbol);
  return found ? 1 : 0;
}
static struct json *scanner_visitor_flag_set(struct json_visitor *visitor,
                                             struct json *json) {
  int *ret = visitor->extra;
  *ret = 1;
  return json;
}
int scanner_contains_typedef(YYSCAN_TYPE decl) {
  struct json *json = json_json_obj_get(decl, SYMBOL_DECLARATION_SPECIFIERS);
  struct json_visitor visitor = {scanner_visitor_flag_set, SYMBOL_TYPEDEF, NULL,
                                 NULL};
  int ret = 0;
  visitor.extra = &ret;
  json_visitor_visit(&visitor, json);
  return ret;
}
static struct json *scanner_visitor_set_insert(struct json_visitor *visitor,
                                               struct json *json) {
  if (json_is_str(json)) {
    struct json_str *str = json_as_str(json);
    set_insert(visitor->extra, json_str_get(str));
  }
  return json;
}
void scanner_collect_typedef(YYSCAN_EXTRA self, YYSCAN_TYPE decl) {
  struct json *json = json_json_obj_get(decl, SYMBOL_INIT_DECLARATOR_LIST);
  struct json_visitor visitor = {scanner_visitor_set_insert, SYMBOL_IDENTIFIER,
                                 NULL, NULL};
  visitor.extra = self->typedefs;
  json_visitor_visit(&visitor, json);
}
