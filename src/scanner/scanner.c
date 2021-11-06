#include "scanner.h"

#include "json/factory.h"
#include "json/json.h"
#include "json/util.h"
#include "json/visitor.h"
#include "util/symbol.h"
#include "util/util.h"

struct scanner {
  struct json_factory *factory;
  struct json_obj *typedefs;
  YYSCAN_TYPE comma;
  YYSCAN_TYPE top;
};

YYSCAN_EXTRA scanner_new(struct json_factory *factory) {
  YYSCAN_EXTRA self = util_malloc(sizeof(struct scanner));
  self->factory = factory;
  self->typedefs = json_obj_new();
  self->comma = json_new_str(SYMBOL_COMMA);
  self->top = json_null();
  return self;
}
void scanner_del(YYSCAN_EXTRA self) {
  json_del(self->comma);
  json_obj_del(self->typedefs);
  util_free(self);
}
YYSCAN_TYPE scanner_json_token(YYSCAN_EXTRA self, const char *token) {
  token = json_factory_symbol(self->factory, token);
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
  if (json_is_arr(json)) {
    struct json_arr *arr = json_as_arr(json);
    json_arr_push(arr, val);
  }
  return json;
}
YYSCAN_TYPE scanner_json_set(YYSCAN_TYPE json, const char *key,
                             YYSCAN_TYPE val) {
  if (json_is_obj(json)) {
    struct json_obj *obj = json_as_obj(json);
    json_obj_insert(obj, key, val);
  }
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
  return json_obj_has(self->typedefs, symbol);
}
static void scanner_collect_typedef(struct json_visitor *visitor,
                                    struct json *json) {
  if (json_has(json, SYMBOL_DIRECT_DECLARATOR)) {
    struct json_obj *typedefs = json_visit_extra(visitor);
    struct json *identifier = json_get_identifier(json);
    const char *symbol = json_get_str(identifier);
    assert(symbol);
    json_obj_insert(typedefs, symbol, json_null());
  } else {
    json_visit_foreach(visitor, json);
  }
}
void scanner_register_typedef(YYSCAN_EXTRA self, YYSCAN_TYPE decl) {
  struct json *specs = json_get(decl, SYMBOL_DECLARATION_SPECIFIERS);
  struct json *list = json_get(decl, SYMBOL_INIT_DECLARATOR_LIST);
  if (!json_is_null(json_get(specs, SYMBOL_TYPEDEF))) {
    json_visit(scanner_collect_typedef, self->typedefs, list);
  }
}
