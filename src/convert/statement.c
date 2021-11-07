#include "statement.h"

#include "json/json.h"
#include "json/map.h"
#include "util/symbol.h"

static void convert_compound_statement(struct convert_extra *self,
                                       struct json *json) {
  convert_statement(self, json);
}
static void convert_statement_list(struct json_map *map) {
  struct convert_extra *self = json_map_extra(map);
  struct json *json = json_map_val(map);
  convert_statement(self, json);
}

void convert_statement(struct convert_extra *self, struct json *json) {
  if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    convert_compound_statement(self, json_get(json, SYMBOL_COMPOUND_STATEMENT));
  } else if (json_has(json, SYMBOL_STATEMENT_LIST)) {
    json_foreach(json_get(json, SYMBOL_STATEMENT_LIST), convert_statement_list,
                 self);
  }
}
