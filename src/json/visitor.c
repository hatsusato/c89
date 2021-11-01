#include "visitor.h"

#include "json.h"
#include "map.h"
#include "tag.h"
#include "util/util.h"

struct json_visitor_extra {
  struct json_visitor *visitor;
  struct json_obj *parent;
};

static void json_visitor_visit_obj(const char *key, struct json *val,
                                   void *extra) {
  struct json_visitor_extra *tmp = extra;
  struct json_visitor *visitor = tmp->visitor;
  struct json_obj *parent = tmp->parent;
  if (util_streq(visitor->key, key)) {
    visitor->result = NULL;
    visitor->visitor(visitor, val);
    if (visitor->result) {
      json_obj_insert(parent, key, visitor->result);
    }
  }
  json_visitor_visit(visitor, val);
}
static void json_visitor_visit_arr(const char *key, struct json *val,
                                   void *extra) {
  json_visitor_visit(extra, val);
  UTIL_UNUSED(key);
}

void json_visitor_visit(struct json_visitor *self, struct json *json) {
  struct json_visitor_extra extra;
  struct json_map map;
  switch (json_tag(json)) {
  case JSON_TAG_OBJ:
    extra.visitor = self;
    extra.parent = json_as_obj(json);
    map.map = json_visitor_visit_obj;
    map.extra = &extra;
    json_obj_foreach(json_as_obj(json), &map);
    break;
  case JSON_TAG_ARR:
    map.map = json_visitor_visit_arr;
    map.extra = self;
    json_arr_foreach(json_as_arr(json), &map);
    break;
  default:
    break;
  }
}
