#include "declaration.h"

#include "expression.h"
#include "json/json.h"
#include "json/map.h"
#include "type.h"
#include "util/symbol.h"

static struct json *convert_initializer(struct convert *, struct json *);

static void convert_init_declarator(struct convert *self, struct json *json) {
  struct json *identifier = json_find_identifier(json);
  convert_push_symbol(self, identifier);
  if (json_has(json, SYMBOL_INITIALIZER)) {
    struct json *value =
        convert_initializer(self, json_get(json, SYMBOL_INITIALIZER));
    struct json *pointer = convert_lookup_symbol(self, identifier);
    struct json *instr = convert_push_instr(self, "store");
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
    return convert_rvalue(self, json_get(json, SYMBOL_ASSIGNMENT_EXPRESSION));
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
