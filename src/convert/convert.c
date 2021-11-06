#include "convert.h"

#include "json/factory.h"
#include "json/json.h"
#include "json/util.h"
#include "json/visitor.h"
#include "util/symbol.h"

struct convert_extra {
  struct json_factory *factory;
  struct json_arr *module;
};

struct json *convert_get_identifier(struct json *json) {
  while (!json_is_null(json)) {
    json = json_get(json, SYMBOL_DIRECT_DECLARATOR);
    if (json_has(json, SYMBOL_IDENTIFIER)) {
      return json_get(json, SYMBOL_IDENTIFIER);
    }
  }
  return json;
}
static void convert_visitor(struct json_visitor *visitor, struct json *json) {
  if (json_has(json, SYMBOL_FUNCTION_DEFINITION)) {
    struct convert_extra *self = visitor->extra;
    struct json *func = json_factory_obj(self->factory);
    json_set(func, "name", convert_get_identifier(json));
    json_arr_push(self->module, func);
  }
  json_visit_foreach(visitor, json);
}
void convert(struct json_factory *factory, struct json *json) {
  struct json_visitor visitor;
  struct convert_extra extra;
  struct json *module = json_factory_arr(factory);
  visitor.visitor = convert_visitor;
  visitor.extra = &extra;
  extra.factory = factory;
  extra.module = json_as_arr(module);
  json_visit(&visitor, json);
  json_set(json, "module", module);
}
