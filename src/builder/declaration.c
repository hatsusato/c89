#include "declaration.h"

#include "expression.h"
#include "ir/function.h"
#include "ir/module.h"
#include "json/json.h"
#include "json/map.h"
#include "util/symbol.h"

static void builder_init_declarator(struct json *module, struct json *json) {
  struct json *identifier = json_find_identifier(json);
  const char *name = json_get_str(identifier);
  struct json *pointer = ir_module_new_identifier(module, identifier);
  struct json *function = json_get(module, "current");
  ir_function_insert_symbol(function, name, pointer);
  json_del(pointer);
  if (json_has(json, SYMBOL_ASSIGN)) {
    struct json *value = builder_rvalue(function, json);
    if (ir_module_is_global_scope(module)) {
      pointer = ir_function_lookup_symbol(function, name);
      json_insert(pointer, "init", value);
    } else {
      struct json *instr = ir_module_new_instr(module, "store");
      json_insert(instr, "value", value);
      json_insert(instr, "pointer", pointer);
      json_del(instr);
    }
  }
}
static void builder_init_declarator_list(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  builder_init_declarator(module, json);
}
static void builder_declaration_list(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  builder_declaration(module, json);
}

void builder_declaration(struct json *module, struct json *json) {
  if (json_has(json, SYMBOL_INIT_DECLARATOR_LIST)) {
    json_foreach(json_get(json, SYMBOL_INIT_DECLARATOR_LIST),
                 builder_init_declarator_list, module);
  } else if (json_has(json, SYMBOL_DECLARATION_LIST)) {
    json_foreach(json_get(json, SYMBOL_DECLARATION_LIST),
                 builder_declaration_list, module);
  }
}
