#include "visitor.h"

#include "json.h"
#include "map.h"
#include "tag.h"

struct json_visitor {
  json_visitor_t visitor;
  void *extra;
};

void json_visit(json_visitor_t visitor, void *extra, struct json *json) {
  struct json_visitor self;
  self.visitor = visitor;
  self.extra = extra;
  visitor(&self, json);
}
void *json_visit_extra(struct json_visitor *self) {
  return self->extra;
}
static void json_visit_map(struct json_map *map) {
  struct json_visitor *self = json_map_extra(map);
  self->visitor(self, json_map_val(map));
}
void json_visit_foreach(struct json_visitor *self, struct json *json) {
  switch (json_tag(json)) {
  case JSON_TAG_ARR:
    json_arr_foreach(json_as_arr(json), json_visit_map, self);
    break;
  case JSON_TAG_OBJ:
    json_obj_foreach(json_as_obj(json), json_visit_map, self);
    break;
  default:
    break;
  }
}
