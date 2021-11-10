#include "convert.h"

#include "declaration.h"
#include "function.h"
#include "global.h"
#include "ir/module.h"
#include "json/json.h"
#include "json/map.h"
#include "module.h"
#include "util/symbol.h"

static void convert_external_declaration(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  if (json_has(json, SYMBOL_FUNCTION_DEFINITION)) {
    convert_function_definition(module,
                                json_get(json, SYMBOL_FUNCTION_DEFINITION));
  } else if (json_has(json, SYMBOL_DECLARATION)) {
    convert_declaration(module, json_get(json, SYMBOL_DECLARATION));
  }
}
static void convert_translation_unit(struct json *module, struct json *json) {
  convert_global_init(module);
  json_foreach(json, convert_external_declaration, module);
  convert_global_finish(module);
}

struct json *convert(struct json *json) {
  struct json *translation_unit = json_get(json, SYMBOL_TRANSLATION_UNIT);
  struct json *module = ir_module_new();
  convert_translation_unit(module, translation_unit);
  return module;
}
