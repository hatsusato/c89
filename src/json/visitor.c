#include "visitor.h"

#include "json.h"
#include "map.h"
#include "util/util.h"

static void json_visitor2_map(struct json_map *map) {
  json_visitor2_visit(map->extra, map->val);
}
void json_visitor2_visit(struct json_visitor2 *self, struct json *json) {
  struct json_map map;
  map.map = json_visitor2_map;
  map.extra = self;
  self->visitor(self, json);
  if (json_is_obj(json)) {
    json_obj_foreach(json_as_obj(json), &map);
  } else if (json_is_arr(json)) {
    json_arr_foreach(json_as_arr(json), &map);
  }
}
