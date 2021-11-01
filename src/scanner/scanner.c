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
YYSCAN_TYPE scanner_json_push(YYSCAN_TYPE json, YYSCAN_TYPE val) {
  struct json_arr *arr = json_as_arr(json);
  assert(arr);
  json_arr_push(arr, val);
  return json;
}
YYSCAN_TYPE scanner_json_set(YYSCAN_TYPE json, const char *key,
                             YYSCAN_TYPE val) {
  struct json_obj *obj = json_as_obj(json);
  assert(obj);
  json_obj_insert(obj, key, val);
  return json;
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
static void scanner_visitor_flag_set(struct json *json, void *extra) {
  bool_t *ret = extra;
  *ret = true;
  UTIL_UNUSED(json);
}
int scanner_contains_typedef(YYSCAN_TYPE decl) {
  bool_t ret = false;
  if (json_is_obj(decl)) {
    struct json_obj *obj = json_as_obj(decl);
    struct json *json = json_obj_get(obj, SYMBOL_DECLARATION_SPECIFIERS);
    json_visitor_visit(scanner_visitor_flag_set, SYMBOL_TYPEDEF, json, &ret);
  }
  return ret;
}
static void scanner_visitor_set_insert(struct json *json, void *extra) {
  if (json_is_str(json)) {
    struct json_str *str = json_as_str(json);
    set_insert(extra, json_str_get(str));
  }
}
void scanner_collect_typedef(YYSCAN_EXTRA self, YYSCAN_TYPE decl) {
  if (json_is_obj(decl)) {
    struct json_obj *obj = json_as_obj(decl);
    struct json *json = json_obj_get(obj, SYMBOL_INIT_DECLARATOR_LIST);
    json_visitor_visit(scanner_visitor_set_insert, SYMBOL_IDENTIFIER, json,
                       self->typedefs);
  }
}
