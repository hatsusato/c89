#include "default.h"

#include "json/json.h"
#include "json/map.h"
#include "json/visitor.h"
#include "util/symbol.h"

static bool_t convert_default_statement(struct json *);
static bool_t convert_default_labeled_statement(struct json *json) {
  if (json_has(json, SYMBOL_DEFAULT)) {
    return true;
  } else {
    return convert_default_statement(json_obj_get(json, SYMBOL_STATEMENT));
  }
}
static void convert_default_statement_list(struct json_map *map) {
  bool_t *has_default = json_map_extra(map);
  struct json *json = json_map_val(map);
  if (convert_default_statement(json)) {
    *has_default = true;
    json_map_finish(map);
  }
}
static bool_t convert_default_compound_statement(struct json *json) {
  bool_t has_default = false;
  json_foreach(json_obj_get(json, SYMBOL_STATEMENT_LIST),
               convert_default_statement_list, &has_default);
  return has_default;
}
static bool_t convert_default_selection_statement(struct json *json) {
  if (json_has(json, SYMBOL_IF)) {
    bool_t then_has_default =
        convert_default_statement(json_obj_get(json, SYMBOL_THEN_STATEMENT));
    bool_t else_has_default =
        json_has(json, SYMBOL_ELSE) &&
        convert_default_statement(json_obj_get(json, SYMBOL_ELSE_STATEMENT));
    return then_has_default || else_has_default;
  } else {
    convert_default_statement(json_obj_get(json, SYMBOL_STATEMENT));
    return false;
  }
}
static bool_t convert_default_statement(struct json *json) {
  bool_t has_default = false;
  if (json_has(json, SYMBOL_LABELED_STATEMENT)) {
    json = json_obj_get(json, SYMBOL_LABELED_STATEMENT);
    has_default = convert_default_labeled_statement(json);
  } else if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    json = json_obj_get(json, SYMBOL_COMPOUND_STATEMENT);
    has_default = convert_default_compound_statement(json);
  } else if (json_has(json, SYMBOL_SELECTION_STATEMENT)) {
    json = json_obj_get(json, SYMBOL_SELECTION_STATEMENT);
    has_default = convert_default_selection_statement(json);
  }
  if (has_default) {
    json_obj_insert(json, SYMBOL_HAS_DEFAULT, json_null());
  }
  return has_default;
}
static void convert_default_visitor(struct json_visitor *visitor,
                                    struct json *json) {
  if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    convert_default_compound_statement(
        json_obj_get(json, SYMBOL_COMPOUND_STATEMENT));
  } else {
    json_visit_foreach(visitor, json);
  }
}

void convert_default(struct json *json) {
  json_visit(convert_default_visitor, NULL, json);
}
