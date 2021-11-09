#include "convert.h"

#include "function.h"
#include "json/json.h"
#include "json/map.h"
#include "statement.h"
#include "type.h"
#include "util/symbol.h"

static void convert_function_definition(struct convert *self,
                                        struct json *json) {
  struct json *module = convert_get_module(self);
  struct json *name = json_find_identifier(json);
  convert_function_set_name(module, name);
  convert_push_block(module);
  convert_statement(module, json);
}
static void convert_external_declaration(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  if (json_has(json, SYMBOL_FUNCTION_DEFINITION)) {
    struct convert self;
    self.module = module;
    convert_function_init(module);
    convert_function_definition(&self,
                                json_get(json, SYMBOL_FUNCTION_DEFINITION));
    convert_function_finish(module);
  }
}
static struct json *convert_translation_unit(struct json *json) {
  struct json *module = convert_new_module();
  json_foreach(json, convert_external_declaration, module);
  return module;
}

struct json *convert(struct json *json) {
  struct json *translation_unit = json_get(json, SYMBOL_TRANSLATION_UNIT);
  return convert_translation_unit(translation_unit);
}
