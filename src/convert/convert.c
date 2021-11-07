#include "convert.h"

#include "extra.h"
#include "json/json.h"
#include "json/map.h"
#include "util/symbol.h"

static void convert_function_definition(struct convert_extra *self,
                                        struct json *json) {
  struct json *name = json_find_identifier(json);
  struct json *func = json_new_obj();
  struct json *module = json_new_arr();
  json_insert(func, "name", name);
  json_insert(self->module, "module", module);
  json_push(module, func);
  json_del(func);
}
static void convert_external_declaration(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  if (json_has(json, SYMBOL_FUNCTION_DEFINITION)) {
    struct convert_extra self;
    self.module = module;
    json = json_get(json, SYMBOL_FUNCTION_DEFINITION);
    convert_function_definition(&self, json);
  }
}
static struct json *convert_translation_unit(struct json *json) {
  struct json *module = json_new_obj();
  json_foreach(json, convert_external_declaration, module);
  return module;
}

struct json *convert(struct json *json) {
  struct json *translation_unit = json_get(json, SYMBOL_TRANSLATION_UNIT);
  return convert_translation_unit(translation_unit);
}
