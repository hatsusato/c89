#include "visitor.h"

#include "json.h"
#include "map.h"
#include "tag.h"

void json_visit(json_visitor_t visitor, void *extra, struct json *json) {
  struct json_visitor self;
  self.visitor = visitor;
  self.extra = extra;
  visitor(&self, json);
}
static void json_visit_map(struct json_map *map) {
  struct json_visitor *self = map->extra;
  self->visitor(self, map->val);
}
void json_visit_foreach(struct json_visitor *self, struct json *json) {
  struct json_map map;
  map.map = json_visit_map;
  map.extra = self;
  switch (json_tag(json)) {
  case JSON_TAG_ARR:
    json_arr_foreach(json_as_arr(json), &map);
    break;
  case JSON_TAG_OBJ:
    json_obj_foreach(json_as_obj(json), &map);
    break;
  default:
    break;
  }
}
