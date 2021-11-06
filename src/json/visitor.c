#include "visitor.h"

#include "json.h"
#include "map.h"
#include "tag.h"
#include "util.h"

struct json_visitor {
  json_visitor_t visitor;
  void *extra;
  bool_t finished;
};

void json_visit(json_visitor_t visitor, void *extra, struct json *json) {
  struct json_visitor self;
  self.visitor = visitor;
  self.extra = extra;
  self.finished = false;
  visitor(&self, json);
}
void *json_visit_extra(struct json_visitor *self) {
  return self->extra;
}
void json_visit_finish(struct json_visitor *self) {
  self->finished = true;
}
static void json_visit_map(struct json_map *map) {
  struct json_visitor *self = json_map_extra(map);
  self->visitor(self, json_map_val(map));
  if (self->finished) {
    json_map_finish(map);
  }
}
void json_visit_foreach(struct json_visitor *self, struct json *json) {
  if (!self->finished) {
    json_foreach(json, json_visit_map, self);
  }
}
