#include "declaration.h"

#include "expression.h"
#include "json/json.h"
#include "json/map.h"
#include "table.h"
#include "type.h"
#include "util/symbol.h"

static struct json *convert_initializer(struct convert *, struct json *);

static void convert_init_declarator(struct convert *self, struct json *json) {
  struct json *module = convert_get_module(self);
  struct json *identifier = json_find_identifier(json);
  struct json *pointer = convert_table_insert(module, identifier);
  if (json_has(json, SYMBOL_INITIALIZER)) {
    struct json *value =
        convert_initializer(self, json_get(json, SYMBOL_INITIALIZER));
    struct json *instr = convert_push_instr(module, "store");
    json_insert(instr, "value", value);
    json_insert(instr, "pointer", pointer);
  }
}
static void convert_init_declarator_list(struct json_map *map) {
  struct convert *self = json_map_extra(map);
  struct json *json = json_map_val(map);
  convert_init_declarator(self, json);
}
static struct json *convert_initializer(struct convert *self,
                                        struct json *json) {
  if (json_has(json, SYMBOL_ASSIGNMENT_EXPRESSION)) {
    struct json *module = convert_get_module(self);
    return convert_rvalue(module, json_get(json, SYMBOL_ASSIGNMENT_EXPRESSION));
  } else {
    return json;
  }
}
static void convert_declaration_list(struct json_map *map) {
  struct convert *self = json_map_extra(map);
  struct json *json = json_map_val(map);
  convert_declaration(self, json);
}

void convert_declaration(struct convert *self, struct json *json) {
  if (json_has(json, SYMBOL_INIT_DECLARATOR_LIST)) {
    json_foreach(json_get(json, SYMBOL_INIT_DECLARATOR_LIST),
                 convert_init_declarator_list, self);
  } else if (json_has(json, SYMBOL_DECLARATION_LIST)) {
    json_foreach(json_get(json, SYMBOL_DECLARATION_LIST),
                 convert_declaration_list, self);
  }
}
