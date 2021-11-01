#include "visitor.h"

#include "json.h"
#include "map.h"
#include "tag.h"
#include "util/util.h"

static void json_visitor_visit_obj(const char *key, struct json *val,
                                   void *extra) {
  struct json_visitor *visitor = extra;
  if (util_streq(visitor->key, key)) {
    visitor->result = NULL;
    visitor->visitor(visitor, val);
    if (visitor->result) {
      json_obj_insert(visitor->parent, key, visitor->result);
    }
  }
  json_visitor_recurse(visitor, val);
}
static void json_visitor_visit_arr(const char *key, struct json *val,
                                   void *extra) {
  json_visitor_recurse(extra, val);
  UTIL_UNUSED(key);
}

void json_visitor_recurse(struct json_visitor *self, struct json *json) {
  struct json_map map;
  map.extra = self;
  switch (json_tag(json)) {
  case JSON_TAG_OBJ:
    map.map = json_visitor_visit_obj;
    self->parent = json_as_obj(json);
    json_obj_foreach(json_as_obj(json), &map);
    break;
  case JSON_TAG_ARR:
    map.map = json_visitor_visit_arr;
    json_arr_foreach(json_as_arr(json), &map);
    break;
  default:
    break;
  }
}
void json_visitor_visit(json_visitor_t visitor, const char *key,
                        struct json *json, void *extra) {
  struct json_visitor self = {NULL, NULL, NULL, NULL, NULL};
  self.visitor = visitor;
  self.key = key;
  self.extra = extra;
  json_visitor_recurse(&self, json);
}
