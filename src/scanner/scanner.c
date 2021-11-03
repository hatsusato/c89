#include "scanner.h"

#include "json/factory.h"
#include "json/json.h"
#include "json/visitor.h"
#include "symbol.h"
#include "util/util.h"

struct scanner {
  struct json_factory *factory;
  YYSCAN_TYPE top;
  struct json *typedefs;
};

YYSCAN_EXTRA scanner_new(struct json_factory *factory) {
  YYSCAN_EXTRA self = util_malloc(sizeof(struct scanner));
  self->factory = factory;
  self->top = json_null();
  self->typedefs = json_new_obj();
  return self;
}
void scanner_delete(YYSCAN_EXTRA self) {
  json_delete(self->typedefs);
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
  return json_obj_has(json_as_obj(self->typedefs), symbol);
}
static void scanner_visitor_flag_set(struct json *json, void *extra) {
  struct json *num = extra;
  if (json_is_int(num)) {
    json_int_set(json_as_int(num), 1);
  }
  UTIL_UNUSED(json);
}
static void scanner_visitor_set_insert(struct json *json, void *extra) {
  if (json_is_str(json)) {
    struct json_str *str = json_as_str(json);
    json_obj_insert(json_as_obj(extra), json_str_get(str), json_null());
  }
}
void scanner_register_typedef_old(YYSCAN_EXTRA self, YYSCAN_TYPE decl) {
  if (json_is_obj(decl)) {
    struct json_obj *obj = json_as_obj(decl);
    struct json *declaration_specifiers =
        json_obj_get(obj, SYMBOL_DECLARATION_SPECIFIERS);
    struct json *init_declarator_list =
        json_obj_get(obj, SYMBOL_INIT_DECLARATOR_LIST);
    struct json *extra = json_new_int(0);
    json_visitor_visit(scanner_visitor_flag_set, SYMBOL_TYPEDEF,
                       declaration_specifiers, extra);
    if (UTIL_BOOL(json_int_get(json_as_int(extra)))) {
      json_visitor_visit(scanner_visitor_set_insert, SYMBOL_IDENTIFIER,
                         init_declarator_list, self->typedefs);
    }
    json_delete(extra);
  }
}
static void scanner_find_typedef(struct json_visitor2 *visitor,
                                 struct json *json) {
  if (json_is_obj(json) && json_obj_has(json_as_obj(json), SYMBOL_TYPEDEF)) {
    bool_t *found = visitor->extra;
    *found = true;
  }
}
static void scanner_collect_typedef(struct json_visitor2 *visitor,
                                    struct json *json) {
  if (json_is_obj(json)) {
    struct json *direct =
        json_obj_get(json_as_obj(json), SYMBOL_DIRECT_DECLARATOR);
    if (json_is_obj(direct)) {
      struct json *identifier =
          json_obj_get(json_as_obj(direct), SYMBOL_IDENTIFIER);
      if (json_is_str(identifier)) {
        const char *symbol = json_str_get(json_as_str(identifier));
        struct json_obj *typedefs = visitor->extra;
        json_obj_insert(typedefs, symbol, json_null());
      }
    }
  }
}
void scanner_register_typedef(YYSCAN_EXTRA self, YYSCAN_TYPE decl) {
  struct json_visitor2 visitor;
  bool_t found = false;
  visitor.visitor = scanner_find_typedef;
  visitor.extra = &found;
  json_visitor2_visit(&visitor, json_get(decl, SYMBOL_DECLARATION_SPECIFIERS));
  if (found) {
    visitor.visitor = scanner_collect_typedef;
    visitor.extra = json_as_obj(self->typedefs);
    json_visitor2_visit(&visitor, json_get(decl, SYMBOL_INIT_DECLARATOR_LIST));
  }
}
