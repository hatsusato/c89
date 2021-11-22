#include "return.h"

#include "json/json.h"
#include "json/map.h"
#include "json/visitor.h"
#include "util/symbol.h"
#include "util/util.h"

struct convert_return_extra {
  bool_t must_return;
};

static void convert_return_statement(struct convert_return_extra *,
                                     struct json *);
static void convert_return_statement_list(struct json_map *map) {
  struct convert_return_extra *self = json_map_extra(map);
  struct json *json = json_map_val(map);
  struct convert_return_extra extra;
  extra.must_return = false;
  convert_return_statement(&extra, json);
  if (extra.must_return) {
    self->must_return = true;
    json_map_finish(map);
  }
}
static void convert_return_compound_statement(struct convert_return_extra *self,
                                              struct json *json) {
  struct convert_return_extra extra;
  extra.must_return = false;
  json_foreach(json_obj_get(json, SYMBOL_STATEMENT_LIST),
               convert_return_statement_list, &extra);
  self->must_return = extra.must_return;
}
static void convert_return_selection_statement(
    struct convert_return_extra *self, struct json *json) {
  struct convert_return_extra extra;
  bool_t then_return = false, else_return = false;
  if (json_has(json, SYMBOL_IF)) {
    extra.must_return = false;
    convert_return_statement(&extra, json_obj_get(json, SYMBOL_THEN_STATEMENT));
    then_return = extra.must_return;
  }
  if (json_has(json, SYMBOL_ELSE)) {
    extra.must_return = false;
    convert_return_statement(&extra, json_obj_get(json, SYMBOL_ELSE_STATEMENT));
    else_return = extra.must_return;
  }
  self->must_return = then_return && else_return;
}
static void convert_return_jump_statement(struct convert_return_extra *self,
                                          struct json *json) {
  self->must_return = json_has(json, SYMBOL_RETURN);
}
static void convert_return_statement(struct convert_return_extra *self,
                                     struct json *json) {
  struct convert_return_extra extra;
  extra.must_return = false;
  if (false) {
  } else if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    json = json_obj_get(json, SYMBOL_COMPOUND_STATEMENT);
    convert_return_compound_statement(&extra, json);
  } else if (json_has(json, SYMBOL_SELECTION_STATEMENT)) {
    json = json_obj_get(json, SYMBOL_SELECTION_STATEMENT);
    convert_return_selection_statement(&extra, json);
  } else if (json_has(json, SYMBOL_JUMP_STATEMENT)) {
    json = json_obj_get(json, SYMBOL_JUMP_STATEMENT);
    convert_return_jump_statement(&extra, json);
  }
  if (extra.must_return) {
    json_obj_insert(json, SYMBOL_MUST_RETURN, json_null());
  }
  self->must_return = extra.must_return;
}
static void convert_return_visitor(struct json_visitor *visitor,
                                   struct json *json) {
  if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    struct convert_return_extra extra;
    extra.must_return = false;
    convert_return_compound_statement(
        &extra, json_obj_get(json, SYMBOL_COMPOUND_STATEMENT));
  } else {
    json_visit_foreach(visitor, json);
  }
}

void convert_return(struct json *json) {
  json_visit(convert_return_visitor, NULL, json);
}
