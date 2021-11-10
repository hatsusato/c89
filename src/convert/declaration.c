#include "declaration.h"

#include "alloc.h"
#include "expression.h"
#include "ir/module.h"
#include "ir/table.h"
#include "ir/value.h"
#include "json/json.h"
#include "json/map.h"
#include "module.h"
#include "util/symbol.h"

static void convert_init_declarator(struct json *module, struct json *json) {
  bool_t is_global = ir_table_is_global(module);
  struct json *identifier = json_find_identifier(json);
  const char *name = json_get_str(identifier);
  struct json *pointer =
      is_global ? ir_value_new_global(identifier) : convert_alloc_push(module);
  ir_module_insert_symbol(module, name, pointer);
  json_del(pointer);
  if (json_has(json, SYMBOL_ASSIGN)) {
    struct json *value = convert_rvalue(module, json);
    if (is_global) {
      pointer = ir_module_lookup_symbol(module, name);
      json_insert(pointer, "init", value);
    } else {
      struct json *instr = convert_push_instr(module, "store");
      json_insert(instr, "value", value);
      json_insert(instr, "pointer", pointer);
    }
  }
}
static void convert_init_declarator_list(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  convert_init_declarator(module, json);
}
static void convert_declaration_list(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  convert_declaration(module, json);
}

void convert_declaration(struct json *module, struct json *json) {
  if (json_has(json, SYMBOL_INIT_DECLARATOR_LIST)) {
    json_foreach(json_get(json, SYMBOL_INIT_DECLARATOR_LIST),
                 convert_init_declarator_list, module);
  } else if (json_has(json, SYMBOL_DECLARATION_LIST)) {
    json_foreach(json_get(json, SYMBOL_DECLARATION_LIST),
                 convert_declaration_list, module);
  }
}
