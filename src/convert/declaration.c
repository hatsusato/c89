#include "declaration.h"

#include "alloc.h"
#include "expression.h"
#include "global.h"
#include "json/json.h"
#include "json/map.h"
#include "module.h"
#include "table.h"
#include "util/symbol.h"

static void convert_init_declarator(struct json *module, struct json *json) {
  struct json *identifier = json_find_identifier(json);
  struct json *pointer = convert_alloc_push(module);
  convert_table_insert(module, identifier, pointer);
  json_del(pointer);
  if (json_has(json, SYMBOL_ASSIGN)) {
    struct json *value = convert_rvalue(module, json);
    struct json *instr = convert_push_instr(module, "store");
    json_insert(instr, "value", value);
    json_insert(instr, "pointer", pointer);
  }
}
static void convert_init_declarator_list(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  convert_init_declarator(module, json);
}
static void convert_init_declarator_list_global(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  struct json *identifier = json_find_identifier(json);
  struct json *instr = convert_global_new_value(identifier);
  convert_table_insert(module, identifier, instr);
  json_del(instr);
  if (json_has(json, SYMBOL_ASSIGN)) {
    struct json *value = convert_table_lookup(module, identifier);
    struct json *init = convert_rvalue(module, json);
    json_insert(value, "init", init);
  }
}
static void convert_declaration_list(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  convert_declaration(module, json);
}

void convert_declaration(struct json *module, struct json *json) {
  if (json_has(json, SYMBOL_INIT_DECLARATOR_LIST)) {
    json_map_t map = convert_table_is_global(module)
                         ? convert_init_declarator_list_global
                         : convert_init_declarator_list;
    json_foreach(json_get(json, SYMBOL_INIT_DECLARATOR_LIST), map, module);
  } else if (json_has(json, SYMBOL_DECLARATION_LIST)) {
    json_foreach(json_get(json, SYMBOL_DECLARATION_LIST),
                 convert_declaration_list, module);
  }
}
