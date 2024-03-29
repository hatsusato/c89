#include "builder.h"

#include "declaration.h"
#include "ir/function.h"
#include "ir/module.h"
#include "json/json.h"
#include "json/map.h"
#include "statement.h"
#include "util/symbol.h"

static void builder_function_definition(struct json *module,
                                        struct json *json) {
  struct json *function = ir_module_make_function(module);
  ir_function_init(function, json);
  builder_statement(function, json);
  ir_function_finish(function);
}
static void builder_external_declaration(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  if (json_has(json, SYMBOL_FUNCTION_DEFINITION)) {
    builder_function_definition(module,
                                json_obj_get(json, SYMBOL_FUNCTION_DEFINITION));
  } else if (json_has(json, SYMBOL_DECLARATION)) {
    builder_global_declaration(module, json_obj_get(json, SYMBOL_DECLARATION));
  }
}
static void builder_translation_unit(struct json *module, struct json *json) {
  json_foreach(json, builder_external_declaration, module);
}

struct json *build(struct json *json) {
  struct json *translation_unit = json_obj_get(json, SYMBOL_TRANSLATION_UNIT);
  struct json *module = json_new_obj();
  ir_module_init(module);
  builder_translation_unit(module, translation_unit);
  ir_module_finish(module);
  return module;
}
