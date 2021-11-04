#include "visitor.h"

#include "json.h"
#include "map.h"
#include "tag.h"

static void json_visitor_map(struct json_map *map) {
  json_visit(map->extra, map->val);
}
void json_visit(struct json_visitor *self, struct json *json) {
  struct json_map map;
  map.map = json_visitor_map;
  map.extra = self;
  self->visitor(self, json);
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
