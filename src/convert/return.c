#include "return.h"

#include "json/json.h"
#include "json/map.h"
#include "json/visitor.h"
#include "util/symbol.h"
#include "util/util.h"

enum switch_state {
  SWITCH_STATE_OUTSIDE,
  SWITCH_STATE_BETWEEN,
  SWITCH_STATE_INSIDE
};
enum return_state {
  RETURN_STATE_DEFAULT,
  RETURN_STATE_NEVER,
  RETURN_STATE_MUST
};
struct convert_return_extra {
  enum switch_state switch_state;
  enum return_state return_state;
  bool_t has_default;
};
static void return_state_set(struct convert_return_extra *self,
                             enum return_state state) {
  if (self->return_state == RETURN_STATE_DEFAULT) {
    self->return_state = state;
  }
}
static bool_t return_state_is_must(struct convert_return_extra *self) {
  return self->switch_state == SWITCH_STATE_INSIDE &&
         self->return_state == RETURN_STATE_MUST;
}
static void switch_state_inside(struct convert_return_extra *self) {
  assert(self->switch_state != SWITCH_STATE_OUTSIDE);
  self->switch_state = SWITCH_STATE_INSIDE;
}

static void convert_return_statement(struct convert_return_extra *,
                                     struct json *);
static void convert_return_labeled_statement(struct convert_return_extra *self,
                                             struct json *json) {
  if (json_has(json, SYMBOL_CASE) || json_has(json, SYMBOL_DEFAULT)) {
    if (self->switch_state == SWITCH_STATE_BETWEEN) {
      assert(self->return_state == RETURN_STATE_DEFAULT);
    }
    if (return_state_is_must(self)) {
      self->return_state = RETURN_STATE_DEFAULT;
    }
    switch_state_inside(self);
  }
  if (json_has(json, SYMBOL_DEFAULT)) {
    self->has_default = true;
  }
  convert_return_statement(self, json_obj_get(json, SYMBOL_STATEMENT));
}
static void convert_return_statement_list(struct json_map *map) {
  struct convert_return_extra *self = json_map_extra(map);
  struct json *json = json_map_val(map);
  convert_return_statement(self, json);
}
static void convert_return_compound_statement(struct convert_return_extra *self,
                                              struct json *json) {
  json_foreach(json_obj_get(json, SYMBOL_STATEMENT_LIST),
               convert_return_statement_list, self);
}
static void convert_return_selection_statement(
    struct convert_return_extra *self, struct json *json) {
  if (json_has(json, SYMBOL_SWITCH)) {
    struct convert_return_extra extra = {SWITCH_STATE_BETWEEN,
                                         RETURN_STATE_DEFAULT, false};
    convert_return_statement(&extra, json_obj_get(json, SYMBOL_STATEMENT));
    assert(extra.switch_state != SWITCH_STATE_OUTSIDE);
    if (return_state_is_must(&extra) && extra.has_default) {
      return_state_set(self, RETURN_STATE_MUST);
    }
  } else {
    struct convert_return_extra extra_then = *self, extra_else = *self;
    if (json_has(json, SYMBOL_IF)) {
      convert_return_statement(&extra_then,
                               json_obj_get(json, SYMBOL_THEN_STATEMENT));
    }
    if (json_has(json, SYMBOL_ELSE)) {
      convert_return_statement(&extra_else,
                               json_obj_get(json, SYMBOL_ELSE_STATEMENT));
    }
    if (self->switch_state == SWITCH_STATE_OUTSIDE) {
      assert(extra_then.switch_state == SWITCH_STATE_OUTSIDE);
      assert(extra_else.switch_state == SWITCH_STATE_OUTSIDE);
    }
    if (extra_then.switch_state == SWITCH_STATE_INSIDE ||
        extra_else.switch_state == SWITCH_STATE_INSIDE) {
      switch_state_inside(self);
    }
    if (extra_then.return_state == RETURN_STATE_NEVER ||
        extra_else.return_state == RETURN_STATE_NEVER) {
      return_state_set(self, RETURN_STATE_NEVER);
    } else if (extra_then.return_state == RETURN_STATE_MUST &&
               extra_else.return_state == RETURN_STATE_MUST) {
      return_state_set(self, RETURN_STATE_MUST);
    }
  }
}
static void convert_return_jump_statement(struct convert_return_extra *self,
                                          struct json *json) {
  if (json_has(json, SYMBOL_GOTO)) {
  } else if (json_has(json, SYMBOL_CONTINUE) || json_has(json, SYMBOL_BREAK)) {
    return_state_set(self, RETURN_STATE_NEVER);
  } else if (json_has(json, SYMBOL_RETURN)) {
    return_state_set(self, RETURN_STATE_MUST);
  }
}
static void convert_return_statement(struct convert_return_extra *self,
                                     struct json *json) {
  struct json *child = json_null();
  if (json_has(json, SYMBOL_LABELED_STATEMENT)) {
    child = json_obj_get(json, SYMBOL_LABELED_STATEMENT);
    convert_return_labeled_statement(self, child);
  } else if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    child = json_obj_get(json, SYMBOL_COMPOUND_STATEMENT);
    convert_return_compound_statement(self, child);
  } else if (json_has(json, SYMBOL_SELECTION_STATEMENT)) {
    child = json_obj_get(json, SYMBOL_SELECTION_STATEMENT);
    convert_return_selection_statement(self, child);
  } else if (json_has(json, SYMBOL_JUMP_STATEMENT)) {
    child = json_obj_get(json, SYMBOL_JUMP_STATEMENT);
    convert_return_jump_statement(self, child);
  }
  if (self->return_state == RETURN_STATE_MUST) {
    json_obj_insert(child, SYMBOL_MUST_RETURN, json_null());
    json_obj_insert(json, SYMBOL_MUST_RETURN, json_null());
  }
}
static void convert_return_visitor(struct json_visitor *visitor,
                                   struct json *json) {
  if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    struct convert_return_extra extra = {SWITCH_STATE_OUTSIDE,
                                         RETURN_STATE_DEFAULT, false};
    convert_return_compound_statement(
        &extra, json_obj_get(json, SYMBOL_COMPOUND_STATEMENT));
  } else {
    json_visit_foreach(visitor, json);
  }
}

void convert_return(struct json *json) {
  json_visit(convert_return_visitor, NULL, json);
}
