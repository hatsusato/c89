#include "scanner.h"

#include "json/json.h"
#include "json/set.h"
#include "json/visitor.h"
#include "util/symbol.h"
#include "util/util.h"

struct scanner {
  struct json_set *symbols;
  struct json_obj *typedefs;
  YYSCAN_TYPE top;
};

YYSCAN_EXTRA scanner_new(struct json_set *symbols) {
  YYSCAN_EXTRA self = util_malloc(sizeof(struct scanner));
  self->symbols = symbols;
  self->typedefs = json_obj_new();
  self->top = json_null();
  return self;
}
void scanner_del(YYSCAN_EXTRA self) {
  json_obj_del(self->typedefs);
  util_free(self);
}
YYSCAN_TYPE scanner_json_token(YYSCAN_EXTRA self, const char *token) {
  return json_new_str(json_set_insert(self->symbols, token));
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
static void scanner_find_typedef(struct json_visitor *visitor,
                                 struct json *json) {
  if (json_has(json, SYMBOL_TYPEDEF)) {
    bool_t *found = json_visit_extra(visitor);
    *found = true;
    json_visit_finish(visitor);
  } else {
    json_visit_foreach(visitor, json);
  }
}
static void scanner_collect_typedef(struct json_visitor *visitor,
                                    struct json *json) {
  if (json_has(json, SYMBOL_DIRECT_DECLARATOR)) {
    struct json_obj *typedefs = json_visit_extra(visitor);
    struct json *identifier = json_find_identifier(json);
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
  bool_t found = false;
  json_visit(scanner_find_typedef, &found, specs);
  if (found) {
    json_visit(scanner_collect_typedef, self->typedefs, list);
  }
}
