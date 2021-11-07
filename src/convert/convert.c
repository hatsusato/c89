#include "convert.h"

#include "json/json.h"
#include "json/util.h"
#include "json/visitor.h"
#include "util/symbol.h"

struct convert_extra {
  struct json_arr *module;
};

static void convert_visitor(struct json_visitor *visitor, struct json *json) {
  if (json_has(json, SYMBOL_FUNCTION_DEFINITION)) {
    struct convert_extra *self = json_visit_extra(visitor);
    struct json *func = json_new_obj();
    json_insert(func, "name", json_find_identifier(json));
    json_arr_push(self->module, func);
    json_del(func);
  }
  json_visit_foreach(visitor, json);
}
void convert(struct json *json) {
  struct convert_extra extra;
  struct json *module = json_new_arr();
  extra.module = json_as_arr(module);
  json_visit(convert_visitor, &extra, json);
  json_insert(json, "module", module);
  json_del(module);
}
