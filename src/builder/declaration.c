#include "declaration.h"

#include "expression.h"
#include "ir/function.h"
#include "ir/module.h"
#include "ir/table.h"
#include "ir/value.h"
#include "json/json.h"
#include "json/map.h"
#include "util/symbol.h"

static void builder_init_declarator(struct json *function, struct json *json) {
  struct json *identifier = json_find_identifier(json);
  const char *name = json_get_str(identifier);
  struct json *pointer = ir_function_new_alloca(function);
  ir_function_insert_symbol(function, name, pointer);
  json_del(pointer);
  if (json_has(json, SYMBOL_ASSIGN)) {
    struct json *value = builder_rvalue(function, json);
    struct json *instr = ir_function_make_instr(function, "store");
    json_insert(instr, "value", value);
    json_insert(instr, "pointer", pointer);
  }
}
static void builder_global_init_declarator(struct json *module,
                                           struct json *json) {
  struct json *identifier = json_find_identifier(json);
  struct json *pointer = ir_module_make_global(module, identifier);
  if (json_has(json, SYMBOL_ASSIGN)) {
    struct json *value = builder_global_rvalue(json);
    ir_module_insert_global(module, pointer);
    json_insert(pointer, "init", value);
  }
}
static void builder_init_declarator_list(struct json_map *map) {
  struct json *function = json_map_extra(map);
  struct json *json = json_map_val(map);
  builder_init_declarator(function, json);
}
static void builder_global_init_declarator_list(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  builder_global_init_declarator(module, json);
}
static void builder_declaration_list(struct json_map *map) {
  struct json *function = json_map_extra(map);
  struct json *json = json_map_val(map);
  builder_declaration(function, json);
}
static void builder_global_declaration_list(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  builder_global_declaration(module, json);
}

void builder_declaration(struct json *function, struct json *json) {
  if (json_has(json, SYMBOL_INIT_DECLARATOR_LIST)) {
    json_foreach(json_get(json, SYMBOL_INIT_DECLARATOR_LIST),
                 builder_init_declarator_list, function);
  } else if (json_has(json, SYMBOL_DECLARATION_LIST)) {
    json_foreach(json_get(json, SYMBOL_DECLARATION_LIST),
                 builder_declaration_list, function);
  }
}
void builder_global_declaration(struct json *module, struct json *json) {
  if (json_has(json, SYMBOL_INIT_DECLARATOR_LIST)) {
    json_foreach(json_get(json, SYMBOL_INIT_DECLARATOR_LIST),
                 builder_global_init_declarator_list, module);
  } else if (json_has(json, SYMBOL_DECLARATION_LIST)) {
    json_foreach(json_get(json, SYMBOL_DECLARATION_LIST),
                 builder_global_declaration_list, module);
  }
}
