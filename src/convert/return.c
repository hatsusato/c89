#include "return.h"

#include "json/json.h"
#include "json/map.h"
#include "json/visitor.h"
#include "util/symbol.h"

struct convert_return_extra {
  bool_t must_return;
};

static bool_t convert_return_statement(struct json *);
static void convert_return_statement_list(struct json_map *map) {
  struct convert_return_extra *extra = json_map_extra(map);
  struct json *json = json_map_val(map);
  if (convert_return_statement(json)) {
    extra->must_return = true;
    json_map_finish(map);
  }
}
static bool_t convert_return_compound_statement(struct json *json) {
  struct convert_return_extra extra;
  extra.must_return = false;
  json_foreach(json_obj_get(json, SYMBOL_STATEMENT_LIST),
               convert_return_statement_list, &extra);
  return extra.must_return;
}
static bool_t convert_return_selection_statement(struct json *json) {
  if (json_has(json, SYMBOL_IF)) {
    bool_t then_must_return =
        convert_return_statement(json_obj_get(json, SYMBOL_THEN_STATEMENT));
    if (json_has(json, SYMBOL_ELSE)) {
      bool_t else_must_return =
          convert_return_statement(json_obj_get(json, SYMBOL_ELSE_STATEMENT));
      return then_must_return && else_must_return;
    }
  }
  return false;
}
static bool_t convert_return_jump_statement(struct json *json) {
  return json_has(json, SYMBOL_RETURN);
}
static bool_t convert_return_statement(struct json *json) {
  bool_t must_return = false;
  if (false) {
  } else if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    json = json_obj_get(json, SYMBOL_COMPOUND_STATEMENT);
    must_return = convert_return_compound_statement(json);
  } else if (json_has(json, SYMBOL_SELECTION_STATEMENT)) {
    json = json_obj_get(json, SYMBOL_SELECTION_STATEMENT);
    must_return = convert_return_selection_statement(json);
  } else if (json_has(json, SYMBOL_JUMP_STATEMENT)) {
    json = json_obj_get(json, SYMBOL_JUMP_STATEMENT);
    must_return = convert_return_jump_statement(json);
  }
  if (must_return) {
    json_obj_insert(json, SYMBOL_MUST_RETURN, json_null());
  }
  return must_return;
}
static void convert_return_visitor(struct json_visitor *visitor,
                                   struct json *json) {
  if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    convert_return_compound_statement(
        json_obj_get(json, SYMBOL_COMPOUND_STATEMENT));
  } else {
    json_visit_foreach(visitor, json);
  }
}

void convert_return(struct json *json) {
  json_visit(convert_return_visitor, NULL, json);
}
