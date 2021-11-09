#include "declaration.h"

#include "expression.h"
#include "json/json.h"
#include "json/map.h"
#include "module.h"
#include "table.h"
#include "util/symbol.h"

static struct json *convert_initializer(struct json *, struct json *);

static void convert_init_declarator(struct json *module, struct json *json) {
  struct json *identifier = json_find_identifier(json);
  struct json *pointer = convert_table_insert(module, identifier);
  if (json_has(json, SYMBOL_INITIALIZER)) {
    struct json *value =
        convert_initializer(module, json_get(json, SYMBOL_INITIALIZER));
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
static struct json *convert_initializer(struct json *module,
                                        struct json *json) {
  if (json_has(json, SYMBOL_ASSIGNMENT_EXPRESSION)) {
    return convert_rvalue(module, json_get(json, SYMBOL_ASSIGNMENT_EXPRESSION));
  } else {
    return json;
  }
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
