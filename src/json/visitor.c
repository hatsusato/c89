#include "visitor.h"

#include "json.h"
#include "map.h"
#include "type.h"
#include "util/util.h"

static void json_visitor_visit_obj(struct json *json,
                                   struct json_map_extra *extra) {
  struct json_visitor *visitor = extra->extra;
  if (util_streq(visitor->key, extra->key)) {
    visitor->visitor(visitor, json);
  }
  json_visitor_visit(visitor, json);
}
static void json_visitor_visit_arr(struct json *json,
                                   struct json_map_extra *extra) {
  struct json_visitor *visitor = extra->extra;
  json_visitor_visit(visitor, json);
}

void json_visitor_visit(struct json_visitor *self, struct json *json) {
  struct json_map map;
  switch (json->tag) {
  case JSON_TAG_OBJ:
    map.map = json_visitor_visit_obj;
    map.extra = self;
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
