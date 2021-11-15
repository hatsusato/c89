#include "return.h"

#include "json/json.h"
#include "json/map.h"
#include "json/visitor.h"
#include "util/symbol.h"

static bool_t convert_return_statement(struct json *);

static bool_t convert_return_jump_statement(struct json *json) {
  return json_has(json, SYMBOL_RETURN);
}
static void convert_return_statement_list_map(struct json_map *map) {
  bool_t *has_return = json_map_extra(map);
  struct json *json = json_map_val(map);
  if (convert_return_statement(json)) {
    *has_return = true;
    json_map_finish(map);
  }
}
static bool_t convert_return_compound_statement(struct json *json) {
  bool_t has_return = false;
  json_foreach(json_get(json, SYMBOL_STATEMENT_LIST),
               convert_return_statement_list_map, &has_return);
  return has_return;
}
static bool_t convert_return_statement(struct json *json) {
  bool_t has_return = false;
  if (false) {
  } else if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    has_return = convert_return_compound_statement(
        json_get(json, SYMBOL_COMPOUND_STATEMENT));
  } else if (json_has(json, SYMBOL_JUMP_STATEMENT)) {
    has_return =
        convert_return_jump_statement(json_get(json, SYMBOL_JUMP_STATEMENT));
  }
  if (has_return) {
    json_insert(json, "has-return", json_null());
  }
  return has_return;
}
static void convert_return_visitor(struct json_visitor *visitor,
                                   struct json *json) {
  if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    bool_t has_return = false;
    json = json_get(json, SYMBOL_COMPOUND_STATEMENT);
    json = json_get(json, SYMBOL_STATEMENT_LIST);
    json_foreach(json, convert_return_statement_list_map, &has_return);
  } else {
    json_visit_foreach(visitor, json);
  }
}

void convert_return(struct json *json) {
  json_visit(convert_return_visitor, NULL, json);
}
