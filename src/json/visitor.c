#include "visitor.h"

#include "json.h"
#include "map.h"
#include "util/util.h"

struct json_visitor {
  json_visitor_t visitor;
  const char *key;
  struct json *result;
  struct json *parent;
  void *extra;
};

static void json_visitor_recurse(struct json_visitor *, struct json *);
static void json_visitor_map(struct json_map *map) {
  struct json_visitor *visitor = map->extra;
  if (map->is_obj && util_streq(visitor->key, map->key)) {
    visitor->result = NULL;
    visitor->visitor(map->val, visitor->extra);
    if (visitor->result) {
      json_obj_insert(json_as_obj(visitor->parent), map->key, visitor->result);
    }
  }
  json_visitor_recurse(visitor, map->val);
}
static void json_visitor_recurse(struct json_visitor *self, struct json *json) {
  struct json_map map;
  map.map = json_visitor_map;
  map.extra = self;
  if (json_is_obj(json)) {
    self->parent = json;
    json_obj_foreach(json_as_obj(json), &map);
  } else if (json_is_arr(json)) {
    json_arr_foreach(json_as_arr(json), &map);
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
