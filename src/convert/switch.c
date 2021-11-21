#include "switch.h"

#include "json/json.h"
#include "json/visitor.h"
#include "util/symbol.h"

static void convert_switch_set_fall_through(struct json *json) {
  if (json_has(json, SYMBOL_LABELED_STATEMENT)) {
    json = json_obj_get(json, SYMBOL_LABELED_STATEMENT);
    if (json_has(json, SYMBOL_CASE)) {
      json_obj_insert(json, SYMBOL_FALL_THROUGH, json_null());
    }
  }
}
static void convert_switch_visitor(struct json_visitor *visitor,
                                   struct json *json) {
  if (json_has(json, SYMBOL_CASE)) {
    convert_switch_set_fall_through(json_obj_get(json, SYMBOL_STATEMENT));
  }
  json_visit_foreach(visitor, json);
}

void convert_switch(struct json *json) {
  json_visit(convert_switch_visitor, NULL, json);
}
