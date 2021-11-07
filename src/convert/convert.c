#include "convert.h"

#include "extra.h"
#include "json/json.h"
#include "json/map.h"
#include "json/util.h"
#include "json/visitor.h"
#include "util/symbol.h"

void convert_function_definition(struct convert_extra *self,
                                 struct json *json) {
  struct json *name = json_find_identifier(json);
  struct json *func = json_new_obj();
  json_insert(func, "name", name);
  json_push(self->module, func);
  json_del(func);
}
void convert_external_declaration(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  if (json_has(json, SYMBOL_FUNCTION_DEFINITION)) {
    struct convert_extra self;
    self.module = module;
    json = json_get(json, SYMBOL_FUNCTION_DEFINITION);
    convert_function_definition(&self, json);
  }
}
struct json *convert_translation_unit(struct json *json) {
  struct json *module = json_new_arr();
  json_foreach(json, convert_external_declaration, module);
  return module;
}

static void convert_visitor(struct json_visitor *visitor, struct json *json) {
  if (json_has(json, SYMBOL_FUNCTION_DEFINITION)) {
    struct convert_extra *self = json_visit_extra(visitor);
    convert_function_definition(self,
                                json_get(json, SYMBOL_FUNCTION_DEFINITION));
  }
  json_visit_foreach(visitor, json);
}
void convert(struct json *json) {
  struct convert_extra extra;
  struct json *module = json_new_arr();
  extra.module = module;
  json_visit(convert_visitor, &extra, json);
  json_insert(json, "module", module);
  json_del(module);
}
